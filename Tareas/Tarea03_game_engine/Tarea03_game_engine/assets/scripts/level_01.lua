-- Tabla de elementos del nivel

level = {
	-- Tabla de assets
	assets = {
		[0] = 
		{type = "texture", id = "terrain_img",	path = "./assets/img/terrain.png"},
		{type = "texture", id = "terrain_dark_img",	path = "./assets/img/terrain_dark.png"},
		{type = "texture", id = "frog_idle",	path = "./assets/img/frog_idle.png"},
		{type = "texture", id = "frog_run",		path = "./assets/img/frog_run.png"},
		{type = "texture", id = "frog_fall",	path = "./assets/img/frog_fall.png"},
		{type = "texture", id = "frog_jump",	path = "./assets/img/frog_jump.png"},
		{type = "texture", id = "mushroom_run",	path = "./assets/img/mushroom_run.png"},
		{type = "texture", id = "dark_sky",	path = "./assets/img/backgrounds/dark_sky.png"},
		{type = "texture", id = "dark_houses",	path = "./assets/img/backgrounds/dark_houses.png"}
	},

	-- Tablas de key-action
	keyActions = {
		[0] = 
		{key = "SDLK_UP", action = "jump"},
		{key = "SDLK_RIGHT", action = "move_right"},
		{key = "SDLK_LEFT", action = "move_left"}
	},

	-- Tabla de animaciones
	animations = {
		[0] = 
		{entityType = "player", id = "idle", spriteId = "frog_idle", w = 32, h = 32, numFrames = 11, currentFrame = 01, speedRate = 15, isLoop = true},
		{entityType = "player", id = "fall", spriteId = "frog_fall", w = 32, h = 32, numFrames = 01, currentFrame = 01, speedRate = 01, isLoop = true},
		{entityType = "player", id = "jump", spriteId = "frog_jump", w = 32, h = 32, numFrames = 01, currentFrame = 01, speedRate = 01, isLoop = true},
		{entityType = "player", id = "run",  spriteId = "frog_run",  w = 32, h = 32, numFrames = 12, currentFrame = 01, speedRate = 15, isLoop = true},
		{entityType = "enemy",	id = "run",  spriteId = "mushroom_run",  w = 32, h = 32, numFrames = 16, currentFrame = 01, speedRate = 15, isLoop = true},
	},

	-- Tabla de mapa
	map = {
		path = "./assets/levels/Level1.tmx"
	},

	-- Tabla de entidades
	entities = {
		[0] = 
		{ -- Player
			tag = "player",
			components = {
				animation = {
					numFrames = 11,
					currentFrame = 1,
					frameSpeedRate = 15,
					isLoop = true				
				},
				boxCollider = {
					w = 32,
					h = 32,
					offset = {x = 0.0, y = 0.0}
				},
				cameraFollow = {},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/player.lua"
				},
				sprite = {
					assetId = "frog_idle",
					w = 32,
					h = 32,
					srcRectX = 0,
					srcRectY = 0
				}, 
				transform = {
					position = { x = 17.0, y = 32.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 16,
					currentFrame = 1,
					frameSpeedRate = 15,
					isLoop = true				
				},
				boxCollider = {
					w = 32,
					h = 32,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy.lua"
				},
				sprite = {
					assetId = "mushroom_run",
					w = 32,
					h = 32,
					srcRectX = 0,
					srcRectY = 0
				}, 
				transform = {
					position = { x = 260.0, y = 320.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		}
	}
}
