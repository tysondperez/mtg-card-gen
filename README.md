# mtg-card-gen
Converts .csv files from https://mtg-packs.com/ to a paste-able list compatible with https://draftsim.com/upload-sealed-deck.php.

To use this program, place it in an environment which contains a c code compiler, and in the same directory as your desired csv files.
To get the csv files, I used this MTG Pack Simulator: https://mtg-packs.com/.
Compile the program and then run it with the args being the names of your csv files. For instance, I would run it with ./a.out mtg_pack.csv "mtg_pack (1).csv" "mtg_pack (2).csv" ...
The program will read the names of the cards and their quantities, and add them to an output file named mtgList.txt.
When finished, the txt file will contain the list that can be copied and pasted into the Draftsim deckbuilding environment at https://draftsim.com/upload-sealed-deck.php.
