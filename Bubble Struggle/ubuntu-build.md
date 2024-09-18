# Steps to build on Ubuntu
1. install make and SFML
```bash
sudo apt update
sudo apt install build-essential
sudo apt-get install libsfml-dev
```
2. Run `Make`
```bash
make clean && make
```
3. Copy resources
```bash
cp bubble-struggle/resources/ -r build
```
3. Run built executable
```bash
cd ./build
./project_release
```