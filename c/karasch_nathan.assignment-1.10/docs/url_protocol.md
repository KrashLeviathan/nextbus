# URL Protocol for CyRide NextBus

This document is an attempt to reverse-engineer the URL protocol
for the CyRide NextBus system. The beginning half of the URL is
always going to be
`http://www.nextbus.com/customStopSelector/stopSelectorForIFrame.jsp`.
This is followed by the query string, which is begun with a `?`.

## Query String Format

`?r=____&d=____&s=____&a=____&ts=____`

## Parts

### Route

`r=2E`

This is the bus route. It is usually takes the form of 2E, 2W,
1E, 1W, 1AE, 1AW, etc. However, some bus routes have special
names that may not directly corellate.

### Direction

`d=2E_1_var0`

This is the direction of the bus. Since the bus route name contains
the direction, there is usually only one option here. For route 2E,
the direction is `2E_1_var0`. For route 2W, the direction is
`2W_0_var0`.

As far as I can tell, the format can be broken down like this:

`<route>_<1 for north/east, 0 for south/west>_var0`

This isn't always the case, however. For example, the 9 Plum route
has only one route name and two directions. The route is `9` and
the directions are `9_0_var0` for a north/east direction and
`9_0_var1` for a south/west direction.

### Stop

`s=1123`

This is the starting bus stop number.

### Application

`a=cyride`

I think this is always given the value `cyride`, which would make
sense if there are multiple bus systems in their databases.

### Terminal Stop (Destination)

`ts=1124`

This is the destination bus stop number.

## More

One possible strategy for sorting all the information out (if they
don't come through with an API) may be to write a utility that
generates a local database based on an automation that clicks through
every option on the NextBus page, capturing the URL query and parsing
it for each run through.
