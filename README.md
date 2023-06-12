# Qt mini-projet
### Desc
project based on qt6 in c++, the theme of the game is a vertical scroller

Your score count increase everytime that you shoot on an enemies plane  
You loose live point when an enemies bullet touch you or an enemy plane is below your screen

### How to play
First of all clone that repo  
You control you plane with the arrow (can change it in the params)  
You can change the difficulty in the params
(beginning, medium, hard, impossible, are u ok, powerup)

To install from scratch :
install qt6.5 -> `sudo apt-get install qt6-base-dev qtchooser qmake6 qt6-base-dev-tools qt6-multimedia-dev`  
ATTENTION : you need the multimedia package from qt6  
To check qt version run `qmake -v`

If you want to active developer log mode add in main.cpp :
`Logger::isDevMode=true` at the beginning of the main function


```commandline
git clone --branch miniProjet https://github.com/ackimixs/QT-cpp
cd QT-cpp
cmake .
make
./CPP_QT_TPminiprojet
```

### Setup postgresql
the project use postgresql to store the leaderboard or if you don't want to install it you can use the file system
```commandline
sudo apt-get install postgresql
sudo -u postgres psql
```
```sql
CREATE USER scroller WITH ENCRYPTED PASSWORD 'scroller';
CREATE DATABASE scroller owner scroller;
```
copy the hidden.env file as .env and fill it with your postgresql credential
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

Settings :
- change the key binding
- change the difficulty
- change the music volume

### ATTENTION
#### installation
You need to install the qt multimedia package
#### music
the music do not work on wsl due that wsl don't support audio nativly

# Credit  
## game assets :

- [enemies ship by Pixel-boy](https://www.patreon.com/SparklinLabs?ty=h)
- [background](https://www.gamedeveloperstudio.com)
## Sounds :

- [bullet shoot](https://mixkit.co/free-sound-effects/)
- [game level](https://mixkit.co/free-sound-effects/)
- [extra bonus](https://mixkit.co/free-sound-effects/)