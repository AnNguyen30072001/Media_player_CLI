## MOCK_PROJECT

Create a CLI application for Linux that serves as a basic media files and video files browser/player using C++

1. Application should be able to runs :
	1- From any directory on your computer
	2- From external: USB ( must to mount device and parse file in USB) (Developing)
2. Avaiable options:
	1 - View list of media files in that folder and all sub-folder (audio and video)
		+ Pagination, 25 per page
	2 - Playlists:
		+ List of playlist
		+ View a playlist
		+ Create/Update/Delete a playlist
	3 - Metadata of a file (Taglib): [MAIN FEATURE]
		+ Available from either media list or a playlist
		+ Show metadata of a media file (pretty much anything you can think of as metadata): 
			Audio: Track name, Album, Artist, Duration, Genre, Publisher, Publish Year,...
			Video: Name, Size, Duration, Bitrate, Codec, 
		+ Edit metadata: change value, add new keys,...
 
	4 - Play music from your application using SDL2 libary on other thread.
		+ Play/Pause
		+ Next/Previous
		+ Automatically move to the next song when current song finish
		+ Display current time and duration time

 
	5 - Can change volume of device.