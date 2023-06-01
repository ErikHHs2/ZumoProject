Hoe je git gebruikt voor dummies.

Stap 0(init)zorg dat de volgende applicaties gedownload zijn.

	https://gitforwindows.org

Stap 1(git bash instellen).
	bij deze stap gaan we je global user name en email  instellen .
	gebruik de volgende commands hier voor: 
		git config --global user.name "w3schools-test"
		git config --global user.email "test@w3schools.com"
	vervang hier de W3schools met jouw username en email respectfully.
Stap 2 (Folder init)
	in de volgende stap gaan we git clone gebruiken om de respository te krijgen en ook doen we gelijk git init om de folder te intitaliseren
		Stap 2.1 (git clone)
			maak op een voor jouw duidelijke plek een folder aan ga naar deze folder en druk rechter muisknop 
				windows 10 druk op "git bash here"
				windows 11 druk op "show more options" en daarna "git bash here"
			hierna gaan we naar de website van je ropository en clicken we op de groene knop Code en koppieren we de link van HTTPS
			ga nu naar je git bash instace en type hier "git clone" met hier achter geplakt je HTTPS link
		Stap 2.1 (Init folder)
			We gaan nu naar de zelfde terminal waar we net "Git clone" hebbe en gedaan hier doen we ook gelijk "git init"
Stap 3 (git commit & push)
	In deze stap gaan we een eerste commit doen en het gelijk pushen.
		Stap 3.1 (Nooit in Main werken)
			Een zeer belangrijk iets is dat je door hebt waar je werkt in github doe daarom regelmatig "git branch" en zorg dat het jouw branch is 
		Stap 3.2 (naar de goede Branch)
			Hiervoor gebruiken we "git checkout "jouw repository""
		Stap 3.3 (Commit)
			we gaan nu een eerste commit doen hiervoor moeten wel wat toevoegen naar de commit dit doen we met 
			"git add -A"
			"git commit -m "hier je commit text"
			"git push"

jesse
