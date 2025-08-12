Cheddar is a real time scheduling analysis tool. This program provides services to check schedulability of architectures models.

With Cheddar, you can:

	- Draw scheduling with usual real time schedulers 
	- Compute task response times 
	- Compute processor utilization factor
	- Check for a given scheduling period, if deadlines are met
	- Compute blocking time on shared resources
	- Give information on buffer requirement
	- ...

See http://beru.univ-brest.fr/cheddar for detailed features and user guide.

# HOW TO INSTALL & RUN 

## Windows

To install Cheddar in windows boxes, just unzip the zip file. All necessary DLL are provided.
Then, you can directly click on the binary 'cheddar.exe' of this folder to launch Cheddar.

## Linux

1.  Untar the binaries in the target directory
2.  To be able to run cheddar, the shell variables of the file cheddar.bash must be set. For such a purpose : set CHEDDAR_INSTALL_PATH of cheddar.bash to the location where
you have unzip the Cheddar tar ball
3.  Put cheddar.bash in your configuration login shell (e.g. .bashrc or .profile or .tcsh for example) or use the source shell command as follow :
        source cheddar.bash
4.  Then, you can actually run cheddar as follows :
        ./cheddar

## With VirtualBox

You should be able to run Cheddar on any computer with VirtualBox. For such a purpose:

1. Install Virtual Box on your computer
2. Download the Cheddar virtual hard disk file from here: http://beru.univ-brest.fr/vbox/CHEDDAR_DEV.vdi
3. Create a new Ubuntu 64-bit virtual machine, and load the cheddar_dev.vdi
4. You can now start your virtual machine.
5. Select you keyboard layout (french by default) and connect: password and login are both "cheddar
6. Open a Terminal and go to the directory contained the Cheddar source (~/cheddar/trunk/src)
7. Do "source script/compilelinux.bash" to setup the environment
8. Do "make" to compile (or "make cheddar" if you just want the Cheddar GUI binary)
9. Then, you can actually run cheddar as follows
        ./cheddar

# CONTACT

Feel free to contact us if you have any problems. Cheddar's mailing list (cheddar@listes.univ-brest.fr, need a subscription before posting).


# SPONSORS

The project is/was sponsored by 

- Ellidiss Technologies
- Conseil regional de Bretagne, Conseil general du Finistere and Bretagne Metropole 
- Campus France
- H2020 MOSAR
- BPI France
- Thales DMS and communication
- Universite de Bretagne Occidentale and the Lab-STICC laboratory

# AUTHORS

Cheddar is mainly designed and developed by :

F. Singhoff <singhoff@univ-brest.fr>
J. Legrand <jerome.legrand@ellidiss.com>
H.N. Tran <hai-nam.tran@univ-brest.fr>
A. Plantec <plantec@univ-brest.fr>
S. Rubini <rubini@univ-brest.fr>


Other contributors :

J. Ait Oufella
L. Allache
Y. Allain
I. Atchadam
M. Auer
M. Baert
S. Bothorel
R. Bouaziz
E. Cadour
F. Charlet
N. Chauvin
P.V. Chinh
R. Couillet
V. Cuiec
P. Dissaux
S. Demurget
B. Djika
M. Dridi
S. Edzang
C. Fotsing
R. Frin
V. Gaudel
D. Geffroy
M. Gning
W. Guillo
S. Herry
T. Huertas
J. Hugues
A. Huopana
H. Ihamouten
M. Kerboeuf
H. Lapinoja
T. Lannuzel
G. Laurens
A. Le bot 
L. Lemarchand
S. Li
H. Martin
L. Moal
L. Morin
M. F. Mouflih
C. Muller
C. Mouden
P. Normand
V.A. Nicolas
M. Nivala
G. Oliva
L . Pautet
R. Prevot
A. Sylia 
D. Saulnier
M. Strauss
F. Touahria
E. Thomas
N. Vienne
E. Vilain
N.H. Vuong
B. Zalila
P. Zhang














