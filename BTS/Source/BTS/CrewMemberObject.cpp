// Fill out your copyright notice in the Description page of Project Settings.


#include "CrewMemberObject.h"

UCrewMemberObject::UCrewMemberObject()
{
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
}