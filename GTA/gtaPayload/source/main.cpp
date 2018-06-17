#include "natives.h"
#include "menu.h"
#include "lib.h"

bool init = false;
int frameCount = 0;
Menu menu;
typedef int Hash;
//CREDITS GOES TO DAVID1337HAX
Hash weaponhash[59] = { 0x42BF8A85, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x5FC3C11, 0xC472FE2, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0xA0973D5E, 0x24B17070, 0x60EC506, 0x34A67B97, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xD205520E, 0xBFD21232, 0x92A27487, 0x83839C4, 0xA89CB99E, 0xC0A3098D, 0x7F229F94, 0x7F7497E5, 0x787F0BB, 0xAB564B93, 0x63AB0442, 0x47757124, 0xA3D4D34, 0x3AABBBAA, 0xC734385A, 0xA3D4D34, 0xDC4DB296 };

bool superJump = false;
bool explosiveAmmo = false;
bool explosiveMelee = false;
bool fireAmmo = false;
bool fastWalk = false;
bool fastSwim = false;
bool noStars = false;
bool infiniteAmmo = false;
bool weapons = false;
bool upgrade = false;

void selfLoops() {
	Player player = PLAYER::PLAYER_ID();
    Ped playerPed = PLAYER::PLAYER_PED_ID();
	
	if (superJump) {
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}
	if (explosiveAmmo) {
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}
	if (explosiveMelee) {
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}
	if(fireAmmo){
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
	}
	if(fastWalk){
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);
	}
	if(fastSwim){
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.49);
	}
	if(noStars){
	    PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
	}
	if(infiniteAmmo){
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), 1);
	}
	
    if(weapons){
       for(int i =0; i<56; i++){
        WEAPON::GIVE_WEAPON_TO_PED(playerPed, weaponhash[i],  9999, 0, 1);
		menu.drawFeedNotification("", "All Weapons Given");
		weapons = false;
    }
  }
  if(upgrade) {
	                    Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);
						
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, 5);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "YEEMODZ");
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, 1);
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 1);
						VEHICLE::SET_VEHICLE_MOD(veh, 16, 5, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 12, 2, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 11, 3, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 14, 14, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 15, 3, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 13, 2, 0);
						VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 6);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 3);
						VEHICLE::SET_VEHICLE_MOD(veh, 23, 19, 1);
						VEHICLE::SET_VEHICLE_MOD(veh, 0, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 1, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 2, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 3, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 4, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 5, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 6, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 7, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 8, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 9, 1, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 10, 1, 0);
						upgrade = false;
  }
}
void selfOptions() {
	menu.banner("Self Options");

	bool godmode = PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID());
	menu.option("Godmode").data(godmode).call(PLAYER::SET_PLAYER_INVINCIBLE, PLAYER::PLAYER_ID(), !godmode);

	bool invisibility = !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID());
	menu.option("Invisibility").data(invisibility).call(ENTITY::SET_ENTITY_VISIBLE, PLAYER::PLAYER_PED_ID(), invisibility, false);

	menu.option("Super Jump").toggle(&superJump);
	menu.option("Explosive Ammo").toggle(&explosiveAmmo);
	menu.option("Explosive Melee").toggle(&explosiveMelee);
	menu.option("Fire Ammo").toggle(&fireAmmo);
	menu.option("Fast Walk").toggle(&fastWalk);
	menu.option("Fast Swim").toggle(&fastSwim);
	menu.option("No Wanted Level").toggle(&noStars);
	
}
void weaponOptions(){
	menu.banner("Weapon Options");
	menu.option("InfiniteAmmo").toggle(&infiniteAmmo);
	menu.option("Give All Weapons").toggle(&weapons);
}
void vehSpawnKeyboardHandler(char* text) {
	Hash vehHash = GAMEPLAY::GET_HASH_KEY(text);
	if (STREAMING::IS_MODEL_A_VEHICLE(vehHash)) {
		menu.vehicleToSpawn = vehHash;
	}
	else {
		menu.drawFeedNotification("Invalid vehicle model", "Error");
	}
}


void vehSpawnHandler() {
	if (menu.vehicleToSpawn) {
		if (STREAMING::HAS_MODEL_LOADED(menu.vehicleToSpawn)) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(playerPed, false);
			Vehicle newVehicle = VEHICLE::CREATE_VEHICLE(menu.vehicleToSpawn, myCoords.x, myCoords.y, myCoords.z, ENTITY::GET_ENTITY_HEADING(playerPed), false, false);

			if (ENTITY::DOES_ENTITY_EXIST(newVehicle)) {
				float currentSpeed = 0;

				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, false)) {
					Vehicle currentVehicle = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					currentSpeed = ENTITY::GET_ENTITY_SPEED(currentVehicle);
					VEHICLE::DELETE_VEHICLE(&currentVehicle);
				}

				PED::SET_PED_INTO_VEHICLE(playerPed, newVehicle, -1);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(newVehicle, currentSpeed);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(menu.vehicleToSpawn);
				menu.vehicleToSpawn = 0;
			}
		}
		else {
			STREAMING::REQUEST_MODEL(menu.vehicleToSpawn);
		}
	}
}
void vehicleSpawner() {
	menu.banner("Vehicle Spawner");
	menu.option("Adder").vehicleSpawn(0xB779A091);
	menu.option("Turismo").vehicleSpawn(0x185484E1);
	menu.option("Rhino").vehicleSpawn(0x2EA68690);
	menu.option("Liberator").vehicleSpawn(0xCD93A7DB);
	menu.option("Buzzard").vehicleSpawn(0x2F03547B);
	menu.option("Lazer").vehicleSpawn(0xB39B0AE6);
	menu.option("IDK").vehicleSpawn(0x5262CC1995D07E09);
	
	menu.option("Custom").keyboard(vehSpawnKeyboardHandler, 20);
}

void bannerSettings() {
	menu.banner("Banner Settings");
	menu.option("Color").editColor(&menu.bannerColor, true);
	menu.option("Indicator Color").editColor(&menu.indicatorColor, true);
	menu.option("Text Color").editColor(&menu.bannerTextColor, true);
	menu.option("Text Font").scroller(&menu.titleFont);
}
void optionSettings() {
	menu.banner("Option Settings");
	menu.option("Background Color").editColor(&menu.bodyColor, true);
	menu.option("Scroller Color").editColor(&menu.scrollerColor, true);
	menu.option("Text Active Color").editColor(&menu.optionsActiveColor, true);
	menu.option("Text Inactive Color").editColor(&menu.optionsInactiveColor, true);
	menu.option("Text Font").scroller(&menu.optionsFont);
	menu.option("Max Options").scroller(&menu.maxOptions, 1, 30, false, false);
}
void instructionSettings() {
	menu.banner("Instruction Settings");
	menu.option("Show").toggle(&menu.instructions);
	menu.option("Color").editColor(&menu.instructionsColor, true);
}
void menuSettings() {
	menu.banner("Menu Settings");
	menu.option("Banner Settings").submenu(bannerSettings);
	menu.option("Option Settings").submenu(optionSettings);
	menu.option("Instruction Settings").submenu(instructionSettings);
	menu.option("Sounds").toggle(&menu.sounds);
}

	void carOptions() {
	menu.banner("Vehicle Options");
	menu.option("Fully Upgrade").toggle(&upgrade);

}
void mainMenu() {
	menu.banner("Main Menu");
	menu.option("Self Options").submenu(selfOptions);
	menu.option("Vehicle Spawner").submenu(vehicleSpawner);
	menu.option("Vehicle Options").tip("Customize the car").submenu(carOptions);
	menu.option("Weapons").submenu(weaponOptions);
	menu.option("Settings").tip("Customize the menu").submenu(menuSettings);
}



extern "C" void _main(void) {
	if (!init) {
		initLibs();
		menu = Menu(mainMenu);
		init = true;
	}

	int newFrameCount = GAMEPLAY::GET_FRAME_COUNT();
	if (newFrameCount > frameCount) {
		frameCount = newFrameCount;

		menu.monitorButtons();

		selfLoops();
		vehSpawnHandler();

		if (menu.open) {
			menu.run();
		}
	}
}