from cyaron import Graph
from cyaron import IO
import random
for cases in range(14,21):
    io=IO('sigma'+str(cases)+'.in','sigma'+str(cases)+'.out')
    n=random.randint(500,1000)
    m=random.randint(n-1,10000)
    io.input_writeln(str(n)+' '+str(m)+' '+str(random.randint(0,5)))
    io.input_writeln('1 '+str(random.randint(2,n-1))+' '+str(random.randint(1,1000000)))
    for t in range(0,m-2):
        io.input_writeln(str(random.randint(2,n-1))+' '+str(random.randint(2,n-1))+' '+str(random.randint(1,1000000)))
    pass
    io.input_writeln(str(n)+' '+str(random.randint(2,n-1))+' '+str(random.randint(1,1000000)))
    #tu=Graph.tree(n,0.4,0.25,weight_limit=(1,1000000))
    #io.input_writeln(tu.to_str(shuffle=True))
pass