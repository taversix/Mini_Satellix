--[ plugin: <插件名称> ]--
-- 引入MnsAPI
local api = require("api")
local handlers = {
    -- 手动引入Mns事件名为键
    -- 对应的值为函数名称字符串
    -- 推荐在文件尾部声明响应函数，包含参数args
    event = "on_event"
}

-- 事件函数
function On(event, arg)
    -- 无需修改
    local args = {}
    for part in string.gmatch(arg, "[^|]+") do
        table.insert(args, part)
    end
    if #args == 0 then
        table.insert(args, arg)
    end

    local fn = _G[handlers[event]]
    if fn then fn(args) end
    
end

function on_event(args)
    -- 注意：不能使用local关键字
    -- 推荐使用on_开头命名
end

-- 及时修改 config/plugin.lua 文件