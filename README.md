# FuChan
##Summit
Fuchan is a lightweight 4chan browser.

It allows browsing all the boards and posts, by an easy search interface.

Searchs are done by the JSON APIs. Thumbnails are cached locally, and are re-used by the program if needed.

This software is still in beta state due to its heavy unstabilities, but it's still usable, and fast. It is, however, rapidly RAM consuming due to poor memory management in its source code (Takes about 100 MB every 15 minutes of regular searches).

##Features
<ul>
  <li>Load any board and any thread</li>
  <li>Add threads to your favourites, they'll be loaded on startup</li>
  <li>Dump a complete thread (only pictures) with one click</li>
  <li>Preview any picture in medium size before downloading it</li>
</ul>

##Interface
The current interface allows people to show 15 threads per search. They can, then, open the board they wish to see, by clicking on it ID. This will open another tab containing the selected board.

##Configuration
Users can add threads to their favourites by simply using the "Set as Favourite" button on the top of each thread. The software doesn't use any config file and relies solely on the 4chan JSON API

##Credits
cdunn2001 : https://github.com/open-source-parsers/jsoncpp for making the JSON parser JsonCPP

