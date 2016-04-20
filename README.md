# nextbus

## Authors:

- Nathan Karasch (nkarasch@iastate.edu)
  - Main author. Made this program as a Com S 327 assignment.
- Jeremy Sheaffer (sheaffer@iastate.edu)
  - Extended his command-line argument parser from the
    Com S 327 assignment.
- Mark Lakata (http://stackoverflow.com/users/364818/mark-lakata)
  - Used his curl/curl.h wrapper solution in the CURLplusplus class
    found on [this StackOverflow post](http://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c)

## Compiling:

`$ make`

## Description:

This program interfaces with the NextBus API to display NextBus
information for CyRide in Ames, IA. It can return bus route
information in a variety of formats, based on user input of
route, stop, etc. The user is also able to configure the
program so that they can quickly find out the time of the
next bus heading home or the time of the next bus heading
to school/work without having to manually type all the
optional parameters. The program is meant to be extensible
to other bus lines (not just CyRide), but the target for this
assignment is CyRide, so any special implementation needed
for other bus lines was not tested.

The program curls the NextBus information from an http request,
which comes back in XML form. The program parses the XML and
pulls out data that it will show the user. XML data that can
be reasonably cached and referenced later is saved in the
directory $HOME/.nextbus/. The config.nextbus file is also
created and saved there.

The configuration file holds user-specific information, such
as saved routes/stops and current agency (ex: CyRide). It
also holds integers that represent epoch time for last usage
of nextbus and last download of the route configuration for
the given agency. These are used by the program to determine
if it should use the cached information or download new info
from the NextBus API. Using the cached data is obviously
faster, but you also don't want to use data that's too old.
The user can force using online data with the -o|--online
flag or force using cached data with the -c|--cached flag.
Forcing online can be useful if you know the information is
outdated. Forcing cached can be useful if you don't have
internet and want to look at the cached bus schedule
information, which is probably still accurate.

The most practical usage of the program is the saved route/stop
feature. When you're working late into the night on your
Com S 327 assignment and you're ready to go home, just type
`nextbus home` and get bus arrival estimations without ever
having to leave the terminal! Computer Science and Software
Engineering majors at ISU, you're welcome. ;-)

## Getting Started:

First, you need to run the program once with any parameters,
which will force the program to create a new config file.
If you're not a Cyclone, you'll need to run `nextbus -a` to
list the different NextBus agencies, and then set your desired
agency with `nextbus -A <agency>`. Finally, set variables
for home, work, etc. using `nextbus -S <name> <route> <stop>`.
      
## Usage:

```
nextbus [
          [ <save-name-1> <save-name-2> ...           ]
          [ -a | --agencies                           ]
          [ -A | --AgencyStore  <agency>              ]
          [ -c | --cached                             ]
          [ -h | --help                               ]
          [ -o | --online                             ]
          [ -p | --predictstop  <stop>                ]
          [ -P | --PredictRoute <route> <stop>        ]
          [ -r | --routes                             ]
          [ -S | --Save         <name> <route> <stop> ]
          [ -s | --schedule     <route>               ]
        ]
```

## Flags/Parameters:

### <save-name-1> <save-name-2> ...

Type any of your saved route/stop variables to get
predictions for that route/stop.

Example: `nextbus work1 work2`

### -a | --agencies

Lists all the agencies serviced by NextBus.

### -A | --AgencyStore  <agency>

Stores the given agency as your default agency for
getting schedules and predictions.

### -c | --cached

Forces the program to used cached schedule and route
information. Doesn't work with predictions, since they
always need to be up-to-date information. This can be
useful for getting schedule/route information when
offline.

### -h | --help

Displays information from the README about how to use
the program.

### -o | --online

Forces the program to pull data from online rather
than using cached information. Otherwise the program
will use cached information for schedules and route info
if the information isn't too old.

### -p | --predictstop  <stop>

Shows predictions for all arriving/departing routes
at a given stop number.

Example: `nextbus -p 1166`

### -P | --PredictRoute <route> <stop>

Shows predictions for the given route at the given stop.

Example: `nextbus -P 2E 1123`

### -r | --routes

Lists all routes for the current agency.

### -S | --Save         <name> <route> <stop>

Saves the given route and stop to a variable name that
can be used with `nextbus <save-name-1> <save-name-2> ...`

Example: `nextbus -S home 1W 1166`

### -s | --schedule     <route>

Displays the bus schedule for the given route.

Example: `nextbus -s 2E`

