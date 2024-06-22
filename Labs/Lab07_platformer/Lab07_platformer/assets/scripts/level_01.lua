-- Tabla de elementos del nivel

level = {
	-- Tabla de assets
	assets = {
		[0] = 
		{type = "texture", id = "terrain_img",	path = "./assets/img/terrain.png"},
		{type = "texture", id = "frog_idle",	path = "./assets/img/frog_idle.png"},
		{type = "texture", id = "frog_run",		path = "./assets/img/frog_run.png"},
		{type = "texture", id = "frog_fall",	path = "./assets/img/frog_fall.png"},
		{type = "texture", id = "frog_jump",	path = "./assets/img/frog_jump.png"}
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
		{entityType = "player", id = "run",  spriteId = "frog_run",  w = 32, h = 32, numFrames = 12, currentFrame = 01, speedRate = 15, isLoop = true}
	},

	-- Tabla de mapa
	map = {
		path = "./assets/levels/level_02.tmx"
	},

	-- Tabla de entidades
	entities = {
		[0] = 
		{ -- Player
			tag = "player",
			components = {
				numFrames = 11,
				currentFrame = 1,
				frameSpeedRate = 15,
				isLoop = true
			},
			boxCollider = {
				w = 32,
				h = 32,
				offset = {x = 0, y = 0}
			},
			camaraFollow = {},
			playerData = {}, 
			rigidbody = { 
				isStatic = false,
				mass = 5.0,
				speed = 3.0 * 64.0,
				jumpForce= { x = 0, y = -1200.0 * 64.0 }
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
	}
}
