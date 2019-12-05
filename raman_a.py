from multiprocessing import Process, Queue
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import numpy as np
from serial import Serial
import time
from os import listdir
from os.path import isfile, join
import queue as Q
import msvcrt
from scipy.signal import savgol_filter

#def integ_set():



def func1(queue,queue2):
    
#    ser = Serial("COM7")
    import serial.tools.list_ports
    def find_arduino(serial_number):
        for pinfo in serial.tools.list_ports.comports():
            if pinfo.serial_number == serial_number:
                return serial.Serial(pinfo.device)
        raise IOError("Could not find an arduino - is it plugged in?")
    
    ser = find_arduino(serial_number='7')


#    ser = Serial("COM4",115200)
    
    def kb():
        x=msvcrt.kbhit()
        if x:
            xx=msvcrt.getch()
        else:
            return False
        return xx

    
    
    
    data_buff_size = 3695     
    data = np.zeros(data_buff_size) 
    n_bytes = 7390
    n=3694
    k=0
    kk=0
    kkk=0
    data11=np.zeros(n)
    datax=np.zeros([3,3648])
#    mydata=np.zeros([8,3694])
#    mydatab=np.zeros([2,3694])
    k1=0

    
    def save_file(dmas):

        files = [f for f in listdir('data') if isfile(join('data', f))]
        hh=len(files)+1
        hh1='data/'+str(hh)+'.npy'
        y22 = dmas.astype(dtype=np.float16)
        np.save(hh1, y22)
#        print "logging data for : ", time.time()-t2, " second"
#        print "saving data as : ", hh1 

    
#    def kb():
#        x=msvcrt.kbhit()
#        if x:
#            xx=msvcrt.getch()
#        else:
#            return False
#        return xx
    xx="b"
    ta=time.time()
    while k == 0: 
                
    #    while k==0:
        x=kb()
        try:
            if x != False and x!='\r':
        #         try:         
                 x=x.decode()
                 xx=xx+x
                 print (x,)
                 
            if x!=False and x=='\r':
                
                if xx[1]== "r":        
                    xx2=xx[2:]
                    xx2=int(xx2)
                    if xx2 <= 600000:
                        print ("Reference integration time set to " +str(xx2)+" ms")
                        ser.write(str(xx2))
                    else :
                        print ("Please, integration time between 27 - 600000 ms")
                elif xx[1]== "s":
                    xx2=xx[2:]
                    xx2=int(xx2)
                    if xx2<=600000:
                        print ("Signal integration time set to " +str(xx2)+" ms")
                        ser.write(str(xx2+5000))
                    else:
                        print ("Please, integration time between 27 - 600000 ms")
                elif xx[1]!= "s" and xx[1]!= "r":
                    if xx[1]== "g":
                        save_file(datax)
                        print ("saved")
                    else:
                        print ("please specify reference (r) signal (s) ")
                    
                xx="b"
        except UnicodeDecodeError:
            print ("only number are allowed")
            x=kb()
            xx="b"
        except ValueError:
            xx="b"
            print ("only number are allowed")
        except IndexError:
            xx="b"
            print ("please input number")
    #    time.sleep(0.03)



        kkk=kkk+1         
        rslt = ser.read(n_bytes)
        data = np.fromstring(rslt, dtype=np.uint16)
        ## print "ok ", time.time()-t1
        if data[0] > 12500:
            rslt=rslt[1:-1]
            data = np.fromstring(rslt, dtype=np.uint16)
            kk=ser.read(1)
            print ("error")
        
        a1=np.argmax(data)
#        print a1
        if a1 != 3694 :
            a2=(a1+1)*2
            a2=np.asscalar(a2)
#            print a2.dtype
#            print n_bytes.
            kk2=ser.read(a2)
        
        
#        caa=ser.readline() 
        try:
            print (float(caa))
        except:
            pass
        data=data[:-1]
        data11=np.append(data11,data)
        
        mydata=np.abs((data11[-n:]/3.0)-2900)
        datx=mydata-(np.mean(mydata[2:11]))
        datx=datx[32:(3648+32)]
        
        datax=np.append(datax,[datx],axis=0)
        try:
            datax=datax[-90:]
        except:
            pass

        queue.put(datx)
#        print time.time()-ta
#        ta=time.time()
        
        
#        print data11[:10]
#        print data11[-10:]
#        print "n"

        try :
            x=queue2.get(timeout=0.001)
        except Q.Empty:
            x=4
        
        if x==0:
            print ("begin data logging")
            k1=1
            dmas=np.append(mydata,mydata,1)
            t2=time.time()
        if x==1:
            k1=0
            save_file(dmas,t2)
            
        if k1==1:
            try:
                mydata1=mydata[-512:]
                dmas=np.append(dmas,mydata1,1)
            except ValueError:
                print (mydata.shape)




def func2(queue):
#    from scipy.signal import savgol_filter
    
    time.sleep(0.8)
    win = pg.GraphicsWindow()
    win.setWindowTitle('Data')
    n=3648
    data11=np.zeros(n)
    data22=np.zeros(n)
    global dataave
    dataave=np.zeros([505,n])
    
    
    p1 = win.addPlot()
#       (colspan=2)
#    win.nextRow()
#    p2 = win.addPlot()
#    win.nextRow()
    x=np.linspace(742.61,481.71,n)
    
#    curve1 = p1.plot(x,data11, pen=(255,0,0))
#    curve2 = p1.plot(x,data22, pen=(255,128,0))
#    curve3 = p1.plot(x,data22, pen=(255,255,0))
#    curve4 = p1.plot(x,data22, pen=(0,255,0))
#    curve5 = p1.plot(x,data22, pen=(0,255,128))
#    curve6 = p1.plot(x,data22, pen=(0,128, 128))
#    curve7 = p1.plot(x,data22, pen=(0, 0, 128))
#    curve8 = p1.plot(x,data22, pen=(0, 0, 255))
    curve9 = p1.plot(x,data22, pen=(0,255 , 255))
    p1.setYRange(-30, 2300, padding=0)
    

    
    def update1():
        global dataave
        datx=queue.get(timeout=600)
#        data11=mydata[0]
#        data22=mydata[1]


#        datx = (savgol_filter(mydata[6],33, 3))
        
#        datx = (data11+data22+mydata[5])/3.0
#        dataave=np.append(dataave,[datx],0)
#        dataave=dataave[-5:,:]
#        dataaveb=np.mean(dataave, axis=0)
        
#        datx[:32]=datx[:32]+400
#        datx[-14:]=datx[-14:]+400
#        print np.shape(dataave)
        

        curve9.setData(x,datx)
        
        



#"""
#int tt=  int tt=12;
#        datx = (data22+data11+mydata[4]+mydata[5])/4
#        curve9.setData(datx)
#int tt=8;
# datx = (data22+mydata[6])/2

#int tt=9;
#datx = (data11+data22+mydata[5])/3.0
#"""

    timer = pg.QtCore.QTimer()
    timer.timeout.connect(update1)
    timer.start(50)
    
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()



def func4(queue2):
    
    import csv
    def kb():
        x=msvcrt.kbhit()
        if x:
            xx=msvcrt.getch()
        else:
            return False
        return xx
    k=0
    k2=1
    k3=0
    cons0=0
    cons1=1
    cons2=2
    cons3=3
    saveornot=0
    while k==0:
        x=kb()
        if x != False and x =='\r':
            print ('\r')
            print (x1)
            print (time.time()-ttt)
#            queue5.put(x1)
        if x != False and x!='\r'and x !=';' and x !='<':
            if saveornot == 1:
                x=x.decode()
                print (x,)
                x1=x1+x
        if x != False and x =='<':
            queue2.put(cons1)
            saveornot=0
#            print '\r'
#            print x1
#            queue5.put(x1)
#            x1=x1+' took '+str(time.time()-t22)+' second'
            com=([x1, str(time.time()-t22)])
            files = [f for f in listdir('data_r3/take_1') if isfile(join('data_r3/take_1', f))]
            hh=len(files)+1
            hh='data_r3/take_1/comment/comment_'+str(hh)+'.csv'
            with open(hh,'w') as csvfile:
                w = csv.writer(csvfile)
                w.writerow(com)
        if x != False and x ==';':
            t22=time.time()
            x1="Description : "
            ttt=time.time()
            queue2.put(cons0)
            saveornot=1
        time.sleep(0.03)
        


if __name__ == '__main__':
    queue=Queue()
    queue2=Queue()
#    queue3=Queue()
    queue4=Queue()    

#    queue5=Queue()
#    queue6=Queue()
    
    p1 = Process(target=func1,args=(queue,queue2,))
    p1.start()
    p2 = Process(target=func2,args=(queue,))
    p2.start()

#    p4 = Process(target=func4,args=(queue2,))
#    p4.start()
    
    p1.join()
    p2.join()

#    p4.join()