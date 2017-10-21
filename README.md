# Television Tracker

Python 2.7.13 Script that scrapes IMDB database (API KEY IS REQUIRED), and compares it against an internal database (JSON files within the "data" folder) and returns the list of shows you haven't seen yet.

## Getting Started

Download the repository. Clear out the data in the data folder as this is sample data for tests. Run the addShow() function until you have added all your shows/seasons to the database. You will also need an IMDB API Key which you can simply get by signing up for a developer key (sorry all I can do for you right now). Then simply just run the python main() function whenever you want to know what shows to watch.

More functions/better usability is coming. GUI version is also in production (made but not posted).

### Prerequisites

The only software requirements are Python 2.7.13 (likely will run on any 2.7.x python version). No packages needed outside the preinstalled ones.

### Installing

I suggest using a virtual environment if you have Python 3.x installed so you don't have any Python confliction. Otherwise no installation required.

## Running the tests

You can run the main() or simply the current script if you want to test to see if it works in the command line.

$Path/tvapp.py if you have python 2.x installed.

### Break down into end to end tests

This is an example of what you might get (likely more shows as time passes).

```
Updating your TV Shows. One moment please!
==================================================
ID : 62704 Name : Ballers Season : 3 Episode : 8
All your shows are updated!
==================================================
Which episodes have you watched? Input the ID Number one at a time. Type Esc to escape.
ID Number :
```

### And coding style tests

By entering the "ID" or "esc" you can update your show list or quit with esc. If you enter an ID and there is another episode to watch, that episode will appear immediately.

## Built With

* [Python](https://www.python.org/) - 2.7.13

## Authors

* **Ryan van Huuksloot** - *Initial work*

See also the list of [contributors](https://github.com/RyanvanHuuksloot/televisionTracker_cmdLine/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Television Trackers were my inspiration so I made my own.
