# Qt mini-projet
### Desc
project based on qt6 in c++, the theme of the game is a vertical scroller

Enemies spawn every 3000ms and that time decrease with your score.  
Your score count increase everytime that you shoot on an enemies plane  
You loose live point when an enemies bullet's touch you or an enemy plane is below your screen  


### How to play
First of all clone that repo  
If you want to use the postgres database change the hidden.env file into .env and fill it  
If you want to use the file system to store leaderboard don't change anything  
You control you plane with the arrow (can change it in the params)  
You can change the difficulty in the params
(beginning, medium, hard)

To install from scratch :
install qt6.5 -> `sudo apt-get install qt6-base-dev qtchooser qmake6 qt6-base-dev-tools qt6-multimedia-dev`  
ATTENTION : you need the multimedia package from qt6  
To check qt version

If you want to active developer log mode add in main.cpp :
`Logger::isDevMode=true` at the beginning of the main func


```commandline
git clone https://github.com/ackimixs/QT-cpp
cd QT-cpp
git checkout remotes/origin/miniProjet
cmake .
make
./CPP_QT_TPminiprojet
```

### Setup postgresql
the project use postgresql to store the leaderboard or if you don't want to install it you can use the file system
```commandline
sudo apt-get install postgresql postgresql-contrib
sudo -u postgres psql
```
```sql
CREATE USER scroller WITH ENCRYPTED PASSWORD 'scroller';
CREATE DATABASE scroller owner scroller;
```
fill the .env file in the root of the projet
```dotenv
DB_HOSTNAME=localhost
DB_DBNAME=scoller
DB_USERNAME=scroller
DB_PASSWORD=scroller
```
```commandline
psql -U scroller -d scroller -f ./sql/model.sql
psql -U scroller -d scroller -f ./sql/data.sql
```

### Optional functionality
PowerUp:
- heal : give you one life
- sniper : your bullets are now piercing for 30sec
- missile : you can now shoot every 200ms

Music :
- game level sound
- bullet shoot
- extra bonus


### Credit  
#### game assets :

- [enemies ship by Pixel-boy](https://www.patreon.com/SparklinLabs?ty=h)
- [background](https://www.gamedeveloperstudio.com)
#### Sounds :

- [bullet shoot](https://mixkit.co/free-sound-effects/)
- [game level](https://mixkit.co/free-sound-effects/)
- [extra bonus](https://mixkit.co/free-sound-effects/)