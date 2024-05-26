World = {}
-- defaults for the levels
World.level = 0 -- level number
World.asts = 15 -- number of asteroids on current level
World.speed = 1 -- speed factor of asteroids on current level
World.score = 0 -- culmitive score

function World.newLevel()
	World.asts = World.asts + World.level * 3
	World.speed = math.floor(World.speed * 1.25)
	World.level = World.level + 1
	for i=1,World.asts do
		local angle = (((math.random() / 2) + 0.5) * math.pi) / 2
		local leftxpos = math.random(1, ship.x - 100)
		local rightxpos = math.random(ship.x + 100, WWIDTH)
		if math.random(2) == 1 then
			angle = -angle
			xpos = leftxpos
		else xpos = rightxpos end
		local o = Obj:new({
			["x"] = xpos,
			["y"] = math.random(1, WHEIGHT-1),
			["type"] = "asteroid",
			["angle"] = angle,
			["sides"] = math.random(5, 9),
			["r"] = math.random(23, 47)
		})
		o:updatespeed(ASTSPEED * World.speed)
		table.insert(asts, o)
	end
end

function World.restart()
	World.level = 0
	World.asts = 15
	World.speed = 1
	World.score = 0
	dots = {}
	asts = {}
	World.newLevel()
	ship.x = WWIDTH/2
	ship.y = WHEIGHT/2
	ship.dx = 0
	ship.dy = 0
	ship.angle = -(math.pi / 2)
end