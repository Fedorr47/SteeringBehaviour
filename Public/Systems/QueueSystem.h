#pragma once

// TODO: need to rework this code https://gamedevelopment.tutsplus.com/understanding-steering-behaviors-queue--gamedev-14365t?_ga=2.126717645.1764264281.1727075311-321390289.1726935424

/*
* 
private function getNeighborAhead() :Boid {
	var i:int;
	var ret :Boid = null;
	var qa :Vector3D = velocity.clone();
	
	qa.normalize();
	qa.scaleBy(MAX_QUEUE_AHEAD);
	
	ahead = position.clone().add(qa);
	
	for (i = 0; i < Game.instance.boids.length; i++) {
		var neighbor :Boid = Game.instance.boids[i];
		var d :Number = distance(ahead, neighbor.position);
		
		if (neighbour != this && d <= MAX_QUEUE_RADIUS) {
			ret = neighbor;
			break;
		}
	}
	
	return ret;
}

public function update():void {
	var doorway :Vector3D = getDoorwayPosition();

	steering = seek(doorway); // seek the doorway
	steering = steering + collisionAvoidance(); // avoid obstacles
	steering = steering + queue(); // queue along the way

	steering = truncate (steering, MAX_FORCE);
	steering = steering / mass;

	velocity = truncate (velocity + steering , MAX_SPEED);
	position = position + velocity;

private function queue() :Vector3D {
	var v :Vector3D = velocity.clone();
	var brake :Vector3D = new Vector3D();
	
	var neighbor :Boid = getNeighborAhead();
	if (neighbor != null) {
		brake.x = -steering.x * 0.8;
		brake.y = -steering.y * 0.8;
		
		v.scaleBy( -1);
		brake = brake.add(v);
		brake = brake.add(separation());
		
		if (distance(position, neighbor.position) <= MAX_QUEUE_RADIUS) {
			velocity.scaleBy(0.3);
		}
	}
	return brake;
}

*/