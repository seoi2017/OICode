from cyaron import String
from cyaron import IO
import random
cstr=[]
for cases in range(1,7):
    io=IO('delta'+str(cases)+'.in','delta'+str(cases)+'.out')
    n=random.randint(1,50)
    #print(n)
    io.input_writeln(n)
    for i in range(0,n):
        cstr.append(String.random(random.randint(3,10)))
        #print(cstr[i])
        io.input_writeln(cstr[i])
    pass
    for i in range(0,n):
        cstr.append(String.random(random.randint(3,10)))
    pass
    an=random.randint(1,500)
    #print(an)
    io.input_writeln(an)
    for i in range(0,an):
        #print(String.random(None,charset=cstr))
        io.input_writeln(String.random(None,charset=cstr))
    pass
pass