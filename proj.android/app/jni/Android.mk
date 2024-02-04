LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIResultLayer/UILoseLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIResultLayer/UIRewardLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIResultLayer/UIWinLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIPause/UIPause.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UITextLayer/UISureLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UITextLayer/UITextGeneralLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UITextLayer/UITextLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UITextLayer/UITextSingleLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIControl.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIControlCellBar/UIControlCellBar.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIPauseLayer/UIPauseLayer.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIControlEnergy/UIControlEnergy.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIRemove/UIRemove.cpp \
$(LOCAL_PATH)/../../../Classes/UIControl/UIControlGold/UIControlGold.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Numeric/NumericModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/CellBar/CellBarModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Wave/WaveModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/CharacterModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease00/Disease00Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease04/Disease04Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease01/Disease01Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease05/Disease05Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease02/Disease02Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease06/Disease06Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Disease/DiseaseType/Disease03/Disease03Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/CellModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/Projectile/ProjectileModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/Projectile/ProjectileType/Cell05/Cell05ProjectileModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/Projectile/ProjectileType/Cell00/Cell00ProjectileModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/Projectile/ProjectileType/Cell03/Cell03ProjectileModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/Shooter/Shooter.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/ShootingCellType/Cell05/Cell05Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/ShootingCellType/Cell00/Cell00Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/ShootingCellType/Cell03/Cell03Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/ShootingCell/ShootingCellModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/EffectCell/EffectCellModel.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/EffectCell/EffectCellType/Cell04/Cell04Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/EffectCell/EffectCellType/Cell06/Cell06Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/EffectCell/EffectCellType/Cell01/Cell01Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/EffectCell/EffectCellType/Cell02/Cell02Model.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Character/Cell/EffectCell/Effector/Effector.cpp \
$(LOCAL_PATH)/../../../Classes/Models/Level/LevelModel.cpp \
$(LOCAL_PATH)/../../../Classes/UIComponents/UINotification/UINotification.cpp \
$(LOCAL_PATH)/../../../Classes/UIComponents/UIProgressor/UIProgressor.cpp \
$(LOCAL_PATH)/../../../Classes/UINumeric/UINumeric.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIProjectile/UIProjectile.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIProjectile/ProjectileType/Cell05Projectile/UICell05Projectile.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIProjectile/ProjectileType/Cell00Projectile/UICell00Projectile.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIProjectile/ProjectileType/Cell03Projectile/UICell03Projectile.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIObjects.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICell.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell02/UICell02.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell06/UICell06.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell03/UICell03.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell00/UICell00.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell04/UICell04.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell01/UICell01.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UICell/UICellType/Cell05/UICell05.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDisease.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease00/UIDisease00.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease04/UIDisease04.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease01/UIDisease01.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease05/UIDisease05.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease02/UIDisease02.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease06/UIDisease06.cpp \
$(LOCAL_PATH)/../../../Classes/UIObjects/UIDisease/UIDiseaseType/Disease03/UIDisease03.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/SplashScene/SplashScene.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/LevelScene/LevelButton.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/LevelScene/LevelScene.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/LevelScene/SwitchSceneButton.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/TemplateScene/TemplateScene.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/TemplateScene/Components/TemplateComponent/TemplateComponent.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/MainMenuScene/MMBackgroundLayer.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/MainMenuScene/MMControl.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/MainMenuScene/MainMenuScene.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/MainMenuScene/Components/MMOptions.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/GSBackgroundLayer.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/GSControlLayer.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/GSMap.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/GameScene.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/Components/GSBrick.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/Components/GSFlag.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/GameScene/Components/GSTutorial.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
