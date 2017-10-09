from cyaron import IO
import random
for cases in range(1,7):
    io=IO('beta'+str(cases)+'.in','beta'+str(cases)+'.out')
    io.input_writeln(str(random.randint(1,pow(10,10)))+' '+str(random.randint(1,4)))
pass