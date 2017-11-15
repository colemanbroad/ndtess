def store_ndarray(_fname, _ndarray):

    with open(_fname,"w") as ofi:
        ofi.write(5*" ")
        ofi.write("".join([("%4i" % item) for item in range(_ndarray.shape[1]) ] ))
        ofi.write("\n"+5*" ")
        ofi.write("".join([("%4s" % (3*".")) for item in range(_ndarray.shape[1]) ] ))
        ofi.write("\n")
        for y in range(_ndarray.shape[0]):
            li = "%4i:" % y
            li += "".join([("%4i" % item) for item in _ndarray[y,:] ])
            li += "\n"
            ofi.write(li)

    print(">> wrote ",_fname)
    return

def store_heaplist(_fname, _heap):

    with open(_fname,"w") as ofi:
        for i in range(len(_heap)):
            ofi.write((("%2i" % i) + " > hq from zeros < %4.2f %3i %3i %4.2f") % _heap[i])
            ofi.write("\n")
    print(">> wrote %i items to %s" % (len(_heap),_fname))
    return
