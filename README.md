# qrpmbuild-gui

qrpmbuild-gui is used to generate rpm binary package. 
It's very simple and easy to use,and could pack binary to *.rpm at now.

#Platform:
    Linux, Qt5(what I have tested is openSUSE-Leap-15.0, Qt5.11)

#How to use:
1. Download the source code, compile and run
2. The main interface:
![Alt text](https://github.com/FANCY0047/qrpmbuild-gui/blob/master/screenshot/qrpmbuild-gui-main.png)
    1. input the message of the files you want to pack,
    2. click button(Add File) to select binary file and type in the destination
    3. click button(Generate) to generate RPM package file
    ![Alt text](https://github.com/FANCY0047/qrpmbuild-gui/blob/master/screenshot/qrpmbuild-gui-generate.png)    
    4. click button(Open) to open the folder which contains your RPM package file
    5. run "$rpm -qi [your-package-name].rpm", you can see the infomation of the RPM package file you have just generated
    ![Alt text](https://github.com/FANCY0047/qrpmbuild-gui//master/screenshot/qrpmbuild-gui-rpminfo.png)
