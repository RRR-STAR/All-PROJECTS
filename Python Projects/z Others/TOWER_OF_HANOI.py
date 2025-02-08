def TOH(n, start, mid, end) :
    
    if (n == 1) : # Base case
        print("Move disk 1 from", start, "to", end)
        return
    
    # recursive case
    
    TOH(n - 1, start, end, mid)
    print("Move disk", n, "from", start, "to", end)
    TOH(n - 1, mid, start, end)
    
    return

count = 0
def toh(n, a, b, c) :
    
    global count;  count += 1
    print(count, "no. of times func called\n", a, b, c)
    
    if (n > 0) :
        toh(n - 1, a, c, b)
        if (a) :
            c.append(a.pop())
        toh(n - 1, b, a, c)
    
    return


if (__name__ == "__main__") :
    
    a = [0, 1, 2, 3, 4, 5, 6];  b = [];  c = []
    
    import time
    print("recursion start at ...", time.ctime() )
    
    toh(len(a), a, b, c)
    
    print("recursion ends at ...", time.ctime() )
    