import numpy as np
import heapq


# ----

def show_basic_voronoi_img(coords, img):
    from scipy.spatial import Voronoi, voronoi_plot_2d
    vor = Voronoi(coords)
    fig = voronoi_plot_2d(vor)
    fig.gca().imshow(img.T)
    return fig, vor

# ----

NEIGHBOR_GRID = np.array([(-1, 0), (1, 0), (0, -1), (0, 1)])

def _inbounds(img):
    ymax, xmax = img.shape
    def f(y,x):
        return 0<=y<ymax and 0<=x<xmax
    return f

def distance(f0,f1):
    return np.abs(f0+f1) + 1.0

# ---- 
def _nonrow_major_inbounds(img):
    ymax, xmax = img.shape
    def f(x,y):
        return 0<=x<xmax and 0<=y<ymax
    return f

def initialize_heapq(labimg, distimg, row_major = True):
    heap=[]
    heapq.heapify(heap)
    inbounds = _inbounds(labimg)
    if not row_major:
        inbounds = _nonrow_major_inbounds(labimg)
    print()
    if row_major:
        for y in range(labimg.shape[0]):
            for x in range(labimg.shape[1]):
                l = labimg[y,x]
                if l != 0:
                    for dy,dx in NEIGHBOR_GRID:
                        y2,x2 = y+dy, x+dx
                        if inbounds(y2,x2):
                            d1 = distimg[y,x]
                            d2 = distimg[y2,x2]
                            dist = distance(d1,d2)

                            heapq.heappush(heap, (dist, x2, y2 , l))
                            print(">> (%3i %3i) %4.1f (%3i %3i) %4.1f %4.1f -> %s" % (y,x,d1,y2,x2,d2,l,str(heap[0])))
    else:
        for x in range(labimg.shape[0]):
         for y in range(labimg.shape[1]):
             l = labimg[x,y]
             if l != 0:
                 for dx,dy in NEIGHBOR_GRID:
                     x2,y2 = x+dx, y+dy
                     if inbounds(x2,y2):
                         d1 = distimg[x,y]
                         d2 = distimg[x2, y2]
                         dist = distance(d1,d2)
                         #print(">> (%3i %3i) %4.1f (%3i %3i) %4.1f %4.1f" % (y,x,d1,y2,x2,d2,l))
                         heapq.heappush(heap, (dist, x2, y2, l))
    return heap


def build_vorimg(heap, vorimg_0, distimg, row_major = True):
    """
    tessellate an image by growing existing labeled regions
    """
    vorimg = vorimg_0.copy()

    inbounds = _inbounds(vorimg)
    if not row_major:
        inbounds = _nonrow_major_inbounds(vorimg)
    #print()

    if row_major:
        while len(heap) > 0:
            d,x,y,l = heapq.heappop(heap)
            if vorimg[y,x]==0:
                vorimg[y,x] = l
                for dy,dx in NEIGHBOR_GRID:
                    x2,y2 = x+dx, y+dy
                    if inbounds(y2,x2):
                        nl = vorimg[y2,x2]
                        if nl == 0 : # then unclaimed
                            d1 = distimg[y,x]
                            d2 = distimg[y2,x2]
                            nd = distance(d1,d2) + d
                            heapq.heappush(heap, (nd, x2, y2, l))

    else:
        while len(heap) > 0:
            d,x,y,l = heapq.heappop(heap)
            if vorimg[x,y]==0:
                vorimg[x,y] = l
                for dx, dy in NEIGHBOR_GRID:
                    x2,y2 = x+dx, y+dy
                    if inbounds(x2,y2):
                        nl = vorimg[x2, y2]
                        if nl == 0 : # then unclaimed
                            d1 = distimg[x,y]
                            d2 = distimg[x2, y2]
                            nd = distance(d1,d2) + d
                            heapq.heappush(heap, (nd, x2, y2, l))

    return vorimg

# ----

def tessellate_labimg(labimg, distimg=None, row_major= True):
    #print("[tessellate_labimg] :: ",labimg.shape)
    if distimg is None:
        distimg = np.zeros_like(labimg).astype('float32')
    heap = initialize_heapq(labimg, distimg, row_major)
    vorimg = build_vorimg(heap, labimg, distimg, row_major)
    return vorimg

