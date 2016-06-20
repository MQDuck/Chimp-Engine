distance = getCenterX() - playerGetCenterX()
playerWidth = playerGetWidth()

if distance > playerWidth then
    runLeft()
elseif -distance > playerWidth then
    runRight()
end

jump()

