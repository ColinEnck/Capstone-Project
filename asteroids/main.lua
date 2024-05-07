SHIPH = 15 -- height from shooter tip to base
ANGLEADJ = math.pi / 6 -- adjustment of angle between base points
ANGFAC = 2.5 -- factor of angle adjustment
SHIPSPEED = 5 -- factor of updatating dx and dy based on angle
SHOOTSPEED = 300 -- factor of bullet speed
ASTSPEED = 100 -- slowest asteroid speed

require "obj"
require "world"

function love.load()
    math.randomseed(os.time())

    if not love.window.setMode(0, 0, {["fullscreen"] = true}) then
        print("Could not create window")
        love.event.quit()
    end
    love.window.setTitle("ASTEROIDS!")
    WWIDTH, WHEIGHT = love.graphics.getDimensions()

    shooting = false
    timer = 0
    hit = false -- if just hit an asteroid
    level = 1

    ship = Obj:new({
        ["x"] = WWIDTH / 2,
        ["y"] = WHEIGHT / 2,
        ["type"] = "ship" 
    })

    dots = {} -- list of bullets on the screen
    asts = {} -- list of asteroids on the screen

    World.newLevel()
end

function love.update(dt)
    timer = timer + dt
    if love.keyboard.isDown("a") then
        ship.angle = ship.angle - ANGFAC * dt
    elseif love.keyboard.isDown("d") then
        ship.angle = ship.angle + ANGFAC * dt
    elseif love.keyboard.isDown("w") then
        ship:updatespeed(SHIPSPEED)
    elseif love.keyboard.isDown("s") then
        ship:updatespeed(-SHIPSPEED)
    end

    if shooting and timer >= 0.35 then
        bullet = Obj:new({
            ["x"] = ship.x,
            ["y"] = ship.y,
            ["type"] = "bullet",
            ["angle"] = ship.angle
        })
        bullet:updatespeed(SHOOTSPEED)
        table.insert(dots, 1, bullet) -- queue moves left to right
        if table.getn(dots) > 20 then
            table.remove(dots)
        end
        shooting = false
        timer = 0
    end

    ship:walls()
    ship:update(dt)
    for i,v in ipairs(dots) do
        v:update(dt)
        if v:collision(World) then
            table.remove(dots, i)
            if table.getn(asts) == 0 then
                World.newLevel()
            end
        end
    end
    for i,v in ipairs(asts) do
        v:update(dt)
        v:walls()
    end
    if ship:collision() then
        World.restart()
    end
end

function love.draw()
    ship:draw()
    if table.getn(dots) > 0 then
        for i,v in ipairs(dots) do
            v:draw()
        end
    end
    if table.getn(asts) > 0 then
        for i,v in ipairs(asts) do
            v:draw()
        end
    end
    love.graphics.print(tostring(World.score), 10, 10)
    love.graphics.print("Press ESCAPE to exit", WWIDTH-22*7, 10)
end

function love.keypressed(key)
    if key == "escape" then
        love.event.quit()
    elseif key == "space" then
        shooting = true
    end 
end