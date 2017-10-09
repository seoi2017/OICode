from cyaron import IO
import random
import os
for cases in range(7,21):
    i=open('beta'+str(cases)+'.in','w')
    i.write(str(random.randint(pow(10,10)+1,pow(10,100)))+' '+str(random.randint(5,100)))
    i.close()
    os.system('./std <beta'+str(cases)+'.in>beta'+str(cases)+'.out')
    o=open('beta'+str(cases)+'.out','r')
    c=int(o.readline(2))
    o.close()
    while (c==-1):
        i=open('beta'+str(cases)+'.in','w')
        i.write(str(random.randint(pow(10,10)+1,pow(10,100)))+' '+str(random.randint(5,100)))
        i.close()
        os.system('./std <beta'+str(cases)+'.in>beta'+str(cases)+'.out')
        o=open('beta'+str(cases)+'.out','r')
        c=int(o.readline(2))
        o.close()
    pass
pass