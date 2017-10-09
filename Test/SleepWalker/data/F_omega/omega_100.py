from cyaron import String
from cyaron import IO
import random
cstr=['A','B','A']
for cases in range(7,21):
    io=IO('omega'+str(cases)+'.in','omega'+str(cases)+'.out')
    n=random.randint(100000,500000)
    k=random.randint(11,2000)
    io.input_writeln(str(n)+' '+str(k))
    for i in range(0,n):
        io.input_writeln(cstr[random.randint(0,2)])
    pass
pass