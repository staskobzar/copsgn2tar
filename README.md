## Cisco archives converter

Simple utility to convert Cisco archives *cop.sgn to tar.

### Install
```
git clone https://github.com/staskobzar/copsgn2tar.git
cd copsgn2tar
make
sudo make install
```

### Usage
```
copsgn2tar <PATH_TO_COPSGN_FILE>
```
Will create TAR file in the same directory where source file is with extension *.tar

### Example of usage
When you need to install locale to provision Cisco phones (SIP or SCCP).
Go to the Cisco Suppor website and login. Then find required phone model locale. 
For example here for 7962G:
https://software.cisco.com/download/release.html?mdfid=281346595&softwareid=282074291&os=Linux&release=10.3(2)&relind=AVAILABLE&rellifecycle=&reltype=latest

Then download, convert using this utility and untar: ```tar xvf FILE_PATH```
This will create two more files one of with is another tar archive.
Untar this file and copy locale directory.
For example, if you uncompress tar in ```/tmp``` directory of French/Canada locale, you path would be from ```/tmp/usr/local/cm/tftp/french_canada```.

### Cisco phone provisioning
After you copied the folder to tftp root, update phone configuration file SEP[MAC].cnf.xml to have something like this:
```xml
  <userLocale>
    <name>french_canada</name> <!-- this is name of the folder //-->
    <uid>2</uid>
    <langCode>fr_CA</langCode>
    <version>8.5(3)</version> <!-- check on download page for correct version number -->
  </userLocale>
```
