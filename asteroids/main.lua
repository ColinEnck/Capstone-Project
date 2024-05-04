Obj = {} -- drawable, movable object
Obj.x = 0
Obj.y = 0
Obj.dx = 0
Obj.dy = 0
Obj.angle = -(math.pi / 2)
Obj.type = "" -- can be "ship", "asteroid", or "bullet"
Obj.__index = Obj

function Obj:new()
    return setmetatable({}, self)
end

function Obj:setpos(x, y)
    self.x = x
    self.y = y
end

function Obj:updatespeed(speed)
    self.dx = self.dx + speed * math.cos(self.angle)
    self.dy = self.dy + speed * math.sin(self.angle)
end

function Obj:update(dt)
    self.x = self.x + self.dx * dt
    self.y = self.y + self.dy * dt
end

function Obj:walls()
    if self.x > WINDOWSIZE then
        self.x = 0
    elseif self.x < 0 then
        self.x = WINDOWSIZE
    end
    if self.y > WINDOWSIZE then
        self.y = 0
    elseif self.y < 0 then
        self.y = WINDOWSIZE
    end
end

function Obj:draw()
    if self.type == "ship" then
        love.graphics.polygon(
            "fill",
            -- shooting point
            self.x + SHIPH * math.cos(self.angle),
            self.y + SHIPH * math.sin(self.angle),
            -- facing left, top base point
            self.x - SHIPH * math.cos(self.angle + ANGLEADJ),
            self.y - SHIPH * math.sin(self.angle + ANGLEADJ),
            -- facing left, bottom base point
            self.x - SHIPH * math.cos(self.angle - ANGLEADJ),
            self.y - SHIPH * math.sin(self.angle - ANGLEADJ)
        )
    end
    if self.type == "bullet" then
        love.graphics.circle("fill", self.x, self.y, 3)
    end
end

function love.load()
    WINDOWSIZE = 800 -- size of window (height and width)
    SHIPH = 15 -- height from shooter tip to base
    ANGLEADJ = math.pi / 6 -- adjustment of angle between base points
    ANGFAC = 2.5 -- factor of angle adjustment
    SHIPSPEED = 5 -- factor of updatating dx and dy based on angle
    SHOOTSPEED = 200 -- factor of bullet speed
    COUNTTIME = 20 -- factor of waiting time between bullets

    if not love.window.setMode(WINDOWSIZE, WINDOWSIZE) then
        print("Could not create window")
        love.event.quit()
    end

    ship = Obj:new()
    ship:setpos(WINDOWSIZE / 2, WINDOWSIZE / 2)
    ship.type = "ship"

    shooting = false
    countdown = COUNTTIME
    hit = false -- if just hit an asteroid

    math.randomseed(os.time())

    dots = {} -- list of bullets on the screen
end

function love.update(dt)
    if love.keyboard.isDown("a") then
        ship.angle = ship.angle - ANGFAC * dt
    elseif love.keyboard.isDown("d") then
        ship.angle = ship.angle + ANGFAC * dt
    elseif love.keyboard.isDown("w") then
        ship:updatespeed(SHIPSPEED)
    elseif love.keyboard.isDown("s") then
        ship:updatespeed(-SHIPSPEED)
    end

    if shooting and countdown <= 0 then
        local bullet = Obj:new()
        bullet.x = ship.x
        bullet.y = ship.y
        bullet.angle = ship.angle
        bullet:updatespeed(SHOOTSPEED)
        bullet.type = "bullet"
        table.insert(dots, bullet) 
        shooting = false
        countdown = COUNTTIME + 1
    end

    ship:walls()
    ship:update(dt)
    for k,v in pairs(dots) do
        v:update(dt)
    end

    if hit then countdown = countdown - 10
    else countdown = countdown - 1 end
end

function love.draw()
    ship:draw()
    if table.getn(dots) > 0 then
        for i,v in ipairs(dots) do
            v:draw()
        end
    end
end

function love.keypressed(key)
    if key == "escape" then
        love.event.quit()
    elseif key == "space" then
        shooting = true
    end 
end