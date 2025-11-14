// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include "Logging/StructuredLog.h"
#include "glTFRuntime/Public/glTFRuntimeAsset.h"
#include "glTFRuntime/Public/glTFRuntimeFunctionLibrary.h"
#include "Misc/Paths.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene_root = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = scene_root;

	mesh_component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh_component"));
	mesh_component->AttachToComponent(scene_root, FAttachmentTransformRules::KeepRelativeTransform);
	//mesh_component->SetVisibility(false);

	mesh_component2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh_component2"));
	mesh_component2->AttachToComponent(scene_root, FAttachmentTransformRules::KeepRelativeTransform);
	//mesh_component2->SetVisibility(false);

	FString reference = "/Script/Niagara.NiagaraSystem'/Game/sprite_burst.sprite_burst'";
	niagara_system = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *reference));

	niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("niagara_component"));
	niagara_component->AttachToComponent(mesh_component, FAttachmentTransformRules::KeepRelativeTransform);
	niagara_component->SetAsset(niagara_system);

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	FString mesh_path = FPaths::ProjectDir() + "armchair.glb";
	FglTFRuntimeConfig loader_config;
	UglTFRuntimeAsset* asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(mesh_path, false, loader_config);
	if (!asset) {
		UE_LOGFMT(LogTemp, Error, "Unable to load external file: {0}", mesh_path);
	}

	FglTFRuntimeStaticMeshConfig static_mesh_config;
	static_mesh_config.bBuildLumenCards = true;
	static_mesh_config.bAllowCPUAccess = true;

	static_mesh = asset->LoadStaticMeshRecursive(FString(), TArray<FString>(), static_mesh_config);
	static_mesh->bAllowCPUAccess = true;
	mesh_component->SetStaticMesh((static_mesh == nullptr) ? nullptr : static_mesh);

	//static_mesh2 = asset->LoadStaticMeshRecursive(FString("Object_8"), TArray<FString>(), static_mesh_config);
	//mesh_component2->SetStaticMesh((static_mesh2 == nullptr) ? nullptr : static_mesh2);

	niagara_component->SetVariableObject(FName(TEXT("object_param")), static_mesh);
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

