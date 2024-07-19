-- Tabla de elementos del nivel

level = {
	-- Tabla de assets
	assets = {
		[0] = 
		{type = "texture", id = "terrain_img",	path = "./assets/img/terrain.png"},
		{type = "texture", id = "terrain_cave",	path = "./assets/img/terrain_cave.png"},
		{type = "texture", id = "terrain_dark_img",	path = "./assets/img/terrain_dark.png"},
		{type = "texture", id = "frog_idle",	path = "./assets/img/frog_idle.png"},
		{type = "texture", id = "frog_run",		path = "./assets/img/frog_run.png"},
		{type = "texture", id = "frog_fall",	path = "./assets/img/frog_fall.png"},
		{type = "texture", id = "frog_jump",	path = "./assets/img/frog_jump.png"},
		{type = "texture", id = "mushroom_run",	path = "./assets/img/mushroom_run.png"},
		--Player
		{type = "texture", id = "archer_attack",path = "./assets/img/players/archer/archer_attack.png"},
		{type = "texture", id = "archer_death",	path = "./assets/img/players/archer/archer_death.png"},
		{type = "texture", id = "archer_fall",	path = "./assets/img/players/archer/archer_fall.png"},
		{type = "texture", id = "archer_gethit",path = "./assets/img/players/archer/archer_gethit.png"},
		{type = "texture", id = "archer_idle",	path = "./assets/img/players/archer/archer_idle.png"},
		{type = "texture", id = "archer_jump",	path = "./assets/img/players/archer/archer_jump.png"},
		{type = "texture", id = "archer_run",	path = "./assets/img/players/archer/archer_run.png"},
		--Backgrounds
		{type = "texture", id = "dark_sky",	path = "./assets/img/backgrounds/dark_sky.png"},
		{type = "texture", id = "dark_houses",	path = "./assets/img/backgrounds/dark_houses.png"},
		{type = "texture", id = "cave_bg",	path = "./assets/img/backgrounds/cave.png"},
		{type = "texture", id = "cave_bg2",	path = "./assets/img/backgrounds/cave_bg2.png"},
		{type = "texture", id = "menu1",	path = "./assets/img/menu/menu.png"},
		{type = "texture", id = "ghoticvania_menu",	path = "./assets/img/menu/ghoticvania_menu.png"},
		--Projectiles
		{type = "texture", id = "arrow",	path = "./assets/img/projectiles/arrow.png"},
		--Enemies
		{type = "texture", id = "horse_galloping",	path = "./assets/img/enemies/horse/nightmare-galloping.png"},
		{type = "texture", id = "horse_idle",	path = "./assets/img/enemies/horse/nightmare-idle.png"},
		{type = "texture", id = "flying_eye",	path = "./assets/img/enemies/flying_eye/Flight.png"},
		{type = "texture", id = "mushroom",	path = "./assets/img/enemies/mushroom/Run.png"},
		{type = "texture", id = "goblin",	path = "./assets/img/enemies/goblin/Run.png"},
		--Bosses
		{type = "texture", id = "demon_attack",	path = "./assets/img/bosses/flying_demon/demon-attack.png"},
		{type = "texture", id = "demon_idle",	path = "./assets/img/bosses/flying_demon/demon-idle.png"}
	},

	-- Tablas de key-action
	keyActions = {
		[0] = 
		{key = "SDLK_UP", valueMacro = 1073741906, action = "jump"},
		{key = "SDLK_RIGHT", valueMacro = 1073741903, action = "move_right"},
		{key = "SDLK_LEFT", valueMacro = 1073741904, action = "move_left"},
		{key = "SDLK_SPACE", valueMacro = 32, action = "attack"}
	},

	-- Tablas de backgrounds
	backgrounds = {
		[0] = 
		{asset = "cave_bg2"},
		{asset = "cave_bg"}
	},

	-- Tabla de animaciones
	animations = {
		[0] = 
		--Archer
		{entityType = "player", id = "idle", spriteId = "archer_idle", w = 40, h = 40, numFrames = 10, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		{entityType = "player", id = "fall", spriteId = "archer_fall", w = 40, h = 40, numFrames = 02, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 26},
		{entityType = "player", id = "jump", spriteId = "archer_jump", w = 40, h = 40, numFrames = 02, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		{entityType = "player", id = "run",  spriteId = "archer_run",  w = 40, h = 40, numFrames = 08, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		{entityType = "player", id = "attack",spriteId ="archer_attack",w =40, h = 40, numFrames = 06, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		--flying_eye
		{entityType = "enemy",	id = "run",  spriteId = "flying_eye",w = 50, h = 50, numFrames = 8, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,	srcRectY = 0},
		--flying_eye
		{entityType = "enemy",	id = "run",  spriteId = "mushroom",w = 50, h = 50, numFrames = 8, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,	srcRectY = 0},
		--flying_eye
		{entityType = "enemy",	id = "run",  spriteId = "goblin",w = 50, h = 50, numFrames = 8, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,	srcRectY = 0},
		--Boss
		{entityType = "boss",	id = "run",  spriteId = "demon_attack",w = 240, h = 192, numFrames = 11, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,srcRectY = 0},
		{entityType = "boss",	id = "idle", spriteId = "demon_idle",w = 160, h = 144, numFrames = 6, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,srcRectY = 0}
	},

	-- Tabla de mapa
	map = {
		path = "./assets/levels/Level2.tmx"
	},

	-- Tabla de entidades
	entities = {
		[0] = 
		{ -- Player
			tag = "player",
			components = {
				animation = {
					numFrames = 10,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 40,
					h = 40,
					offset = {x = 0.0, y = 0.0}
				},
				cameraFollow = {},
				rigidbody = { 
					isStatic = false,
					mass = 10.5
				},
				script = {
					path = "./assets/scripts/player.lua"
				},
				sprite = {
					assetId = "archer_idle",
					w = 40,
					h = 40,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 60,  -- Pixels entre imagen de un mismo png
					startRect = 30,  -- Pixels antes de que empiece el png
					flip = true,
				},
				transform = {
					position = { x = 60.0, y = 32.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				},
				projectile = {
					assetId = "arrow",
					speedProjectile = 400,
					mass = 0.5,
					width = 24,
					height = 5
				}
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "flying_eye",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 65,
					spacingRect = 100,
					startRect = 50,
					flip = true,

				}, 
				transform = {
					position = { x = 620.0, y = 150.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "mushroom",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 1004.0, y = 500.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 200.0, y = 600.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "flying_eye",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 65,
					spacingRect = 100,
					startRect = 50,
					flip = true,

				}, 
				transform = {
					position = { x = 500.0, y = 500.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "mushroom",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 100.0, y = 900.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 400.0, y = 1000.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "flying_eye",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 65,
					spacingRect = 100,
					startRect = 50,
					flip = true,

				}, 
				transform = {
					position = { x = 840.0, y = 900.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "mushroom",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 1760.0, y = 750.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 2105.0, y = 650.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "flying_eye",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 65,
					spacingRect = 100,
					startRect = 50,
					flip = true,

				}, 
				transform = {
					position = { x = 2619.0, y = 550.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "mushroom",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 2840.0, y = 420.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 3373.0, y = 520.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "flying_eye",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 65,
					spacingRect = 100,
					startRect = 50,
					flip = true,

				}, 
				transform = {
					position = { x = 3263.0, y = 990.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "mushroom",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 2831.0, y = 760.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 3501.0, y = 820.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "flying_eye",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 65,
					spacingRect = 100,
					startRect = 50,
					flip = true,

				}, 
				transform = {
					position = { x = 3501.0, y = 820.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "mushroom",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 1354.0, y = 120.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 1729.0, y = 70.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 2778.0, y = 100.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 10,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 50,
					h = 50,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy_flip.lua"
				},
				sprite = {
					assetId = "goblin",
					w = 50,
					h = 50,
					srcRectX = 0,
					srcRectY = 50,
					spacingRect = 100,
					startRect = 50,
					flip = true,
				}, 
				transform = {
					position = { x = 2395.0, y = 200.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 360.0
				}			
			}
		},
	}
}
