// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnResourceComponent.h"


// Sets default values for this component's properties
UPawnResourceComponent::UPawnResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UResourceObject* UPawnResourceComponent::GetResourceByType(EResourceType Type)
{
	for (UResourceObject* Resource : ResourceArray)
	{
		if (Resource->ResourceType == Type)
		{
			return Resource;
		}
	}
	return nullptr;
}


// Called when the game starts
void UPawnResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	for (UResourceObject* Resource : ResourceArray)
	{
		Resource->InitResource();
	}
}


// Called every frame
void UPawnResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPawnResourceComponent::OnResourceChanged(UResourceObject* ResourceChanged)
{
	OnResourceChangedEvent.Broadcast(ResourceChanged);
}

