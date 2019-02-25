# vaktija-cli
vaktija for cli, configurable times I'd say

HOME environment variable is necessary to be defined, main server from which data is grabbed is vaktija.ba, shoutout to them. :)
You should have 'vaktija' directory in your home directory and in it file named vaktija.conf in which you should enter the time differences between your city and city of Sarajevo.

Configuration goes something like '+/-minutes' 6 times, divided by spaces each.
(Fajr is between the dawn and sunrise, that's the reason for 6 times)

The configuration supplied works for Novi Pazar (hopefully it will stay that way) so you can use it as example.

ALSO, the program is intended to be run by a script (i.e. vaktija.sh).

Have fun experimenting!
