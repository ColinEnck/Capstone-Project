Obj = {} -- drawable, movable object
Obj.x = 0
Obj.y = 0
Obj.angle = -(math.pi / 2)
Obj.type = "" -- can be "ship", "asteroid", or "bullet"
Obj.dx = 0
Obj.dy = 0
-- only applies to asteroids
Obj.sides = 7
Obj.r = 20
Obj.__index = Obj

function Obj:new(o)
    local o = o or {}
    return setmetatable(o, self)
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
    if self.x > WWIDTH then
        self.x = 0
    elseif self.x < 0 then
        self.x = WWIDTH
    end
    if self.y > WHEIGHT then
        self.y = 0
    elseif self.y < 0 then
        self.y = WHEIGHT
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
    elseif self.type == "bullet" then
        love.graphics.circle("fill", self.x, self.y, 3)
    elseif self.type == "asteroid" then
        love.graphics.circle("line", self.x, self.y, self.r, self.sides)
    end
end

-- returns true if the collision happened
function Obj:collision(World)
    if self.type == "ship" then
        for i,v in ipairs(asts) do
            if math.abs(self.x-v.x) <= v.r and
            math.abs(self.y-v.y) <= v.r then
                return true
            end
        end
    elseif self.type == "bullet" then
        for i,v in ipairs(asts) do
            if math.abs(self.x-v.x) <= (v.r + SHIPH/2) and
            math.abs(self.y-v.y) <= (v.r + SHIPH/2) then
                table.remove(asts, i)
                World.score = World.score + (50 - v.r)
                return true
            end
        end
    end
end