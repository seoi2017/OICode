from cyaron import String
from cyaron import IO
import random
cstr=['A','B']
for cases in range(4,7):
    io=IO('omega'+str(cases)+'.in','omega'+str(cases)+'.out')
    n=random.randint(10000,500000)
    k=random.randint(1,10)
    io.input_writeln(str(n)+' '+str(k))
    for i in range(0,n):
        io.input_writeln(cstr[random.randint(0,1)])
    pass
pass