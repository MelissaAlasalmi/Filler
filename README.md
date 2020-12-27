# Filler
✅  Project score: 100/100  ✅  
Filler is a two-player algorithmic game. The aim is to build an algorithm that fills as much space as possible on a given grid using randomly generated pieces of different sizes and shapes. The pieces cannot be stacked in a way where more than one square falls on top of another and the pieces you place cannot fall on top of the opponent's pieces, either. If any of this happens or any of your pieces fall outside the grid, the game ends. Each successfully placed piece yields points - the goal of the game being to get as many points as possible before the game ends.  
![FillerRound](./RMSrcs/FillerRound.png)  
I used a heatmap to help my program find the optimal place to place a piece. For each round of the game that's played, my program first converts the map received from the filler VM into heatmap by changing '.'s into '0's, and the letters 'o', 'O', 'x' and 'X' to either '-1' (always used to represent my programs' pieces on the map) and '-2' (always used to represent the opponents' pieces on the map). Next, for each coordinate-combo in the heatmap that has '0' value, a new int value is assigned to it based on its relative position to the nearest opponent-owned coordinate:  
![FillerHeatmap](./RMSrcs/FillerHeatmap.png)  
After the first round of the game, to place a new piece, there are several options for my program to choose from. But which one is best? To find this out, I had it scan the playable map area, one coordinate-combo at a time, to search for "sub-map" areas where the piece could potentially fit.  
![FillerPlacement](./RMSrcs/FillerPlacement.png)  
Once the program finds a "sub-map" area where it can place a piece successfully, it stores the coordinate-combo of the top-left corner of the "sub-map" area, then it continues to scan all the remaining "sub-map" areas until it has exhausted all its options. Whenever it finds another viable position, it compares it to the saved coordinate-combo by using sums - the smallest sum suggesting a more optimal area on the map to place the piece!  
![FillerResult](./RMSrcs/Result.png)  
Thanks to the awesome visualizer built by [avocadohooman](https://github.com/avocadohooman/42-filler), here's how it looks when my program goes up against Carli (an opponent player found in the resources directory):  
![MalasalmVSCarli](./RMSrcs/MvsC.gif)  
And how it looks when my program goes up against SuperJeannot (also found in the resources directory):  
![MalasalmVSCarli](./RMSrcs/MvsSJ.gif)  
