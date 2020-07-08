# Treasure-Hunt-Game-Simulation
This is a simulation of a game of treasure hunt for my POO class.
<br/> <br/>In this game there are 4 treasure hunters (starting in each corner of the map), each with a diffrent id and viewing capabilities.
Each traveler will start on the corner position of his viewing zone. If he has a treasure in his viewing sight or more, he will try to get to the closest one 
as fast as possible by moving one space per round. If not, he will go to middle of the table and then move randomly until he will find a 
treasure, get stuck or lose.
<br/><br/>Each of them tries to get to the closest treasure to them as fast as possible. After a treasure is taken, the simulation will continue
until all treasures are taken or all of the treasure hunters are stuck.
<br/>Last one to get a treasure is the one who loses or the ones who get stuck.
<br/><b>The winner is the first one who gets a treasure.</b>
<br/><br/>Treasurer (with id TR) are placed randomly around the map at the start of each simulation (but they can not be placed where treasure
hunters already are).
<ul>
	<li>Traveler with id LL is able to see only under main diagonal of the map and around him by 1 space.</li>
	<li>Traveler with id LU is able to see only above second diagonal of the map and around him by 1 space.</li>
	<li>Traveler with id RU is able to see only above main diagonal of the map and around him by 1 space.</li>
	<li>Traveler with id RL is able to see only under second diagonal of the map and around him by 1 space.</li>
</ul>
