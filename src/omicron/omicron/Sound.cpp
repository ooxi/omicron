/********************************************************************************************************************** 
 * THE OMICRON PROJECT
 *---------------------------------------------------------------------------------------------------------------------
 * Copyright 2010-2013							Electronic Visualization Laboratory, University of Illinois at Chicago
 * Authors:										
 *  Arthur Nishimoto							anishimoto42@gmail.com
 *---------------------------------------------------------------------------------------------------------------------
 * Copyright (c) 2010-2013, Electronic Visualization Laboratory, University of Illinois at Chicago
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
 * following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
 * and the following disclaimer in the documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************************************************/

#include "omicron/Sound.h"

using namespace omicron;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nextBufferID = 10; // Buffers 0 - 9 are considered reserved by the sound system

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound::Sound()
{
	this->soundName = "Sound_"+nextBufferID;
	bufferID = nextBufferID;
	nextBufferID++;
	
	volumeScale = 1.0f;
	volume = 0.5f;
	width = 2.0f;
	wetness = 0.0f;
	roomSize = 0.0f;
	pitch = 1.0f;
	loop = false;
	useEnvironmentParameters = true;

	rolloffMode = Rolloff::None;
	minRolloffDistance = 1.0f;
	maxDistance = 20.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound::Sound(const String& soundName)
{
	this->soundName = soundName;
	bufferID = nextBufferID;
	nextBufferID++;
	
	volumeScale = 1.0f;
	volume = 0.5f;
	width = 2.0f;
	wetness = 0.0f;
	roomSize = 0.0f;
	pitch = 1.0f;
	loop = false;
	useEnvironmentParameters = true;

	rolloffMode = Rolloff::None;
	minRolloffDistance = 1.0f;
	maxDistance = 20.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound::Sound(const String& soundName, float volume, float width, float roomSize, float wetness, bool loop, bool env)
{
	this->soundName = soundName;
	bufferID = nextBufferID;
	nextBufferID++;
	
	volumeScale = 1.0f;
	this->volume = volume;
	this->width = width;
	this->wetness = wetness;
	this->roomSize = roomSize;
	this->loop = loop;
	this->environmentSound = env;
	useEnvironmentParameters = false;

	rolloffMode = Rolloff::None;
	minRolloffDistance = 1.0f;
	maxDistance = 20.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setDefaultParameters(float volume, float width, float roomSize, float wetness, bool loop, bool env)
{
	this->volume = volume;
	this->width = width;
	this->wetness = wetness;
	this->roomSize = roomSize;
	this->loop = loop;
	this->environmentSound = env;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::loadFromFile(const String& filePath)
{
	this->filePath = filePath;

	Message msg("/loadBuffer");
	msg.pushInt32(this->getBufferID());
	msg.pushStr(this->getFilePath());
	environment->getSoundManager()->sendOSCMessage(msg);

	if( environment->getSoundManager()->isSoundServerRunning() )
		ofmsg("Loaded buffer ID %1% with path %2%", %this->getBufferID() %this->getFilePath());
	else
	{
		ofmsg("Attemped to loaded buffer ID %1%, but not connected to a sound server!", %this->getBufferID());
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::loadFromMemory(const void* buf, size_t length)
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDuration()
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setVolumeScale(float volume)
{
	volumeScale = volume;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getVolumeScale()
{
	return volumeScale;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultVolume()
{
	return volume;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultWetness()
{
	return wetness;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultRoomSize()
{
	return roomSize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultWidth()
{
	return width;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getDefaultPitch()
{
	return pitch;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isDefaultLooping()
{
	return loop;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isEnvironmentSound()
{
	return environmentSound;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::resetToEnvironmentParameters()
{
	useEnvironmentParameters = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isUsingEnvironmentParameters()
{
	return useEnvironmentParameters;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setSoundEnvironment(SoundEnvironment* env)
{
	this->environment = env;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundEnvironment* Sound::getSoundEnvironment()
{
	return environment;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setMaxDistance(float value)
{
	this->maxDistance = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getMaxDistance()
{
	return maxDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setMinRolloffDistance(float value)
{
	this->minRolloffDistance = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Sound::getMinRolloffDistance()
{
	return minRolloffDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setDistanceRange(float min, float max)
{
	this->minRolloffDistance = min;
	this->maxDistance = max;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setNoRolloff()
{
	rolloffMode = Rolloff::None;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setLinearRolloff()
{
	rolloffMode = Rolloff::Linear;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sound::setLogarthmicRolloff()
{
	rolloffMode = Rolloff::Logarithmic;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sound::Rolloff Sound::getRolloffMode()
{
	return rolloffMode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isRolloffEnabled()
{
	if( rolloffMode != Rolloff::None )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isRolloffLinear()
{
	if( rolloffMode == Rolloff::Linear )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sound::isRolloffLogarithmic()
{
	if( rolloffMode == Rolloff::Logarithmic )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Sound::getBufferID()
{
	return bufferID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String& Sound::getFilePath()
{
	return filePath;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String& Sound::getName()
{
	return soundName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nextInstanceID = 4001;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundInstance::SoundInstance(Sound* sound)
{
	this->sound = sound;
	instanceID = nextInstanceID; // This should be globally incremented on each new instance. Must be 1001 or greater.
	nextInstanceID++;

	volume = sound->getDefaultVolume();
	width = sound->getDefaultWidth();
	roomSize = sound->getDefaultRoomSize();
	wetness = sound->getDefaultWetness();
	loop = sound->isDefaultLooping();
	environmentSound = sound->isEnvironmentSound();
	pitch = sound->getDefaultPitch();
	
	stereoSound = false;

	rolloffMode = sound->getRolloffMode();
	maxDistance = sound->getMaxDistance();
	minRolloffDistance = sound->getMinRolloffDistance();

	position = Vector3f(0,0,0);
	localPosition = Vector3f(0,0,0);

	environment = sound->getSoundEnvironment();
	environment->getSoundManager()->addInstance(this);
	useEnvironmentParameters = sound->isUsingEnvironmentParameters();

	playState = notPlayed;

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("Created SoundInstance %1% with node ID %2%", %sound->getFilePath() %instanceID);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundInstance::~SoundInstance()
{
	stop();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setLoop(bool value)
{
	loop = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::play()
{
	if( isPlaying() )
		stop();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: Playing buffer %2% with instanceID: %3%", %__FUNCTION__ %sound->getBufferID() %instanceID);

	stereoSound = false;
	Message msg("/play");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	Vector3f audioListener = environment->getUserPosition();
	float newVol = volume;
	/*
	

	// Sound Envelope / Rolloff
	float distanceToListener = Math::sqrt( Math::sqr(audioListener[0] - position[0]) + Math::sqr(audioListener[3] - position[3]) );
	
	if( rolloffMode == Sound::Rolloff::Linear )
	{
		newVol = ( 1 - ((distanceToListener - minRolloffDistance) / maxDistance)) * volume; //Linear rolloff
	}
	else if( rolloffMode == Sound::Rolloff::Logarithmic )
	{
		if( distanceToListener > 0 )
			newVol = minRolloffDistance * (maxDistance / Math::sqr(distanceToListener) );  // Logarithmic
	}
	if( newVol > volume )
		newVol = volume;
	else if( newVol < 0 )
		newVol = 0;
	*/

	float scaledVolume = newVol;
	if( volume * sound->getVolumeScale() > 1 )
	{
		scaledVolume = 1.0;
	}
	else
	{
		scaledVolume =  volume * sound->getVolumeScale();
	}

	msg.pushFloat( scaledVolume );

	// We're assuming the position was set using setPosition() which has already handled the local coordinates
	msg.pushFloat( position[0] );
	msg.pushFloat( position[1] );
	msg.pushFloat( position[2] );
	
	// User's position relative to the audio system
	msg.pushFloat( audioListener[0] );
	msg.pushFloat( audioListener[1] );
	msg.pushFloat( audioListener[2] );

	// Width - nSpeakers 1-20
	if( environmentSound )
		msg.pushFloat( 20 );
	else
		msg.pushFloat( width );

	float wetness = this->wetness;
	float roomSize = this->roomSize;

	if( useEnvironmentParameters )
	{
		wetness = environment->getWetness();
		roomSize = environment->getRoomSize();
	}

	// Mix - wetness of sound 0.0 - 1.0
	msg.pushFloat( wetness );

	// Room size - reverb amount 0.0 - 1.0
	msg.pushFloat( roomSize );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	// Sample rate (1.0 normal, 2.0 one octave up, 0.5 one octave down, -1 backwards
	msg.pushFloat( pitch );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 0 );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 0 );

	// Frame at which you'd like to jump to for playback.  0 is the beginning of the file.
	msg.pushInt32( 0 );

	environment->getSoundManager()->sendOSCMessage(msg);

	playState = playing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::playStereo()
{
	if( isPlaying() )
		stop();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: Playing buffer %2% with instanceID: %3%", %__FUNCTION__ %sound->getBufferID() %instanceID);

	stereoSound = true;
	Message msg("/playStereo");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	float scaledVolume = volume;
	if( volume * sound->getVolumeScale() > 1 )
	{
		scaledVolume = 1.0;
	}
	else
	{
		scaledVolume =  volume * sound->getVolumeScale();
	}
	msg.pushFloat( scaledVolume );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	// Sample rate (1.0 normal, 2.0 one octave up, 0.5 one octave down, -1 backwards
	msg.pushFloat( pitch );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 0 );

	// Frame at which you'd like to jump to for playback.  0 is the beginning of the file.
	msg.pushInt32( 0 );

	environment->getSoundManager()->sendOSCMessage(msg);

	playState = playing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::getLoop()
{
	return loop;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::play( Vector3f position, float volume, float width, float mix, float reverb, bool loop )
{
	if( isPlaying() )
		stop();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: Playing buffer %2% with instanceID: %3%", %__FUNCTION__ %sound->getBufferID() %instanceID);

	stereoSound = false;
	Message msg("/play");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	float scaledVolume = volume;
	if( volume * sound->getVolumeScale() > 1 )
	{
		scaledVolume = 1.0;
	}
	else
	{
		scaledVolume =  volume * sound->getVolumeScale();
	}
	msg.pushFloat( scaledVolume );
	
	// Position in Audio System (local) coordinates
	localPosition = environment->getSoundManager()->worldToLocalPosition( position );
	msg.pushFloat( localPosition[0] );
	msg.pushFloat( localPosition[1] );
	msg.pushFloat( localPosition[2] );
	
	Vector3f audioListener = environment->getUserPosition();
	msg.pushFloat( audioListener[0] );
	msg.pushFloat( audioListener[1] );
	msg.pushFloat( audioListener[2] );

	// Width - nSpeakers 1-20
	msg.pushFloat( width );

	// Mix - wetness of sound 0.0 - 1.0
	msg.pushFloat( wetness );

	// Room size - reverb amount 0.0 - 1.0
	msg.pushFloat( roomSize );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	// Sample rate (1.0 normal, 2.0 one octave up, 0.5 one octave down, -1 backwards
	msg.pushFloat( pitch );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 0 );

	// Frame at which you'd like to jump to for playback.  0 is the beginning of the file.
	msg.pushInt32( 0 );

	environment->getSoundManager()->sendOSCMessage(msg);

	playState = playing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::playStereo( float volume, bool loop )
{
	if( isPlaying() )
		stop();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: Playing buffer %2% with instanceID: %3%", %__FUNCTION__ %sound->getBufferID() %instanceID);

	stereoSound = true;
	Message msg("/playStereo");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	if( volume * sound->getVolumeScale() > 1 )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( volume * sound->getVolumeScale() );
	
	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	// Sample rate (1.0 normal, 2.0 one octave up, 0.5 one octave down, -1 backwards
	msg.pushFloat( pitch );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 0 );

	// Frame at which you'd like to jump to for playback.  0 is the beginning of the file.
	msg.pushInt32( 0 );

	environment->getSoundManager()->sendOSCMessage(msg);

	playState = playing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::playAtFrame( int frameNo )
{
	if( isPlaying() )
		stop();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: Playing buffer %2% with instanceID: %3%", %__FUNCTION__ %sound->getBufferID() %instanceID);

	stereoSound = false;
	Message msg("/play");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	float scaledVolume = volume;
	if( volume * sound->getVolumeScale() > 1 )
	{
		scaledVolume = 1.0;
	}
	else
	{
		scaledVolume =  volume * sound->getVolumeScale();
	}

	msg.pushFloat( scaledVolume );

	// We're assuming the position was set using setPosition() which has already handled the local coordinates
	msg.pushFloat( position[0] );
	msg.pushFloat( position[1] );
	msg.pushFloat( position[2] );
	
	// User's position relative to the audio system
	Vector3f audioListener = environment->getUserPosition();
	msg.pushFloat( audioListener[0] );
	msg.pushFloat( audioListener[1] );
	msg.pushFloat( audioListener[2] );

	// Width - nSpeakers 1-20
	if( environmentSound )
		msg.pushFloat( 20 );
	else
		msg.pushFloat( width );

	float wetness = this->wetness;
	float roomSize = this->roomSize;

	if( useEnvironmentParameters )
	{
		wetness = environment->getWetness();
		roomSize = environment->getRoomSize();
	}

	// Mix - wetness of sound 0.0 - 1.0
	msg.pushFloat( wetness );

	// Room size - reverb amount 0.0 - 1.0
	msg.pushFloat( roomSize );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	// Sample rate (1.0 normal, 2.0 one octave up, 0.5 one octave down, -1 backwards
	msg.pushFloat( pitch );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 1 );

	// Frame at which you'd like to jump to for playback.  0 is the beginning of the file.
	msg.pushInt32( frameNo );

	environment->getSoundManager()->sendOSCMessage(msg);

	playState = playing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::playStereoAtFrame( int frameNo )
{
	if( isPlaying() )
		stop();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: Playing buffer %2% with instanceID: %3%", %__FUNCTION__ %sound->getBufferID() %instanceID);

	stereoSound = true;
	Message msg("/playStereo");
	msg.pushInt32(instanceID);
	msg.pushInt32(sound->getBufferID());

	float scaledVolume = volume;
	if( volume * sound->getVolumeScale() > 1 )
	{
		scaledVolume = 1.0;
	}
	else
	{
		scaledVolume =  volume * sound->getVolumeScale();
	}
	msg.pushFloat( scaledVolume );

	// Loop sound - 0.0 not looping - 1.0 looping
	if( loop )
		msg.pushFloat( 1.0 );
	else
		msg.pushFloat( 0.0 );

	// Sample rate (1.0 normal, 2.0 one octave up, 0.5 one octave down, -1 backwards
	msg.pushFloat( pitch );

	// Trigger for playToPosition ( 0 = off, 1 = on )
	msg.pushInt32( 1 );

	// Frame at which you'd like to jump to for playback.  0 is the beginning of the file.
	msg.pushInt32( frameNo );

	environment->getSoundManager()->sendOSCMessage(msg);

	playState = playing;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::pause()
{
	printf( "%s: Not implemented yet \n", __FUNCTION__);
	playState = paused;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::stop()
{
	//printf( "%s: Freeing instanceID: %d\n", __FUNCTION__, instanceID);
	Message msg("/freeNode");
	msg.pushInt32(instanceID);
	environment->getSoundManager()->sendOSCMessage(msg);

	playState = stopped;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isPlaying()
{
	if( playState == playing )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isDone()
{
	if( playState == stopped )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setPosition(Vector3f pos)
{
	if( isDone() )
		return;

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	position = pos;

	if( isPlaying() )
	{
		Message msg("/setObjectLoc");
		msg.pushInt32(instanceID);

		localPosition = environment->getSoundManager()->worldToLocalPosition( position );

		msg.pushFloat( localPosition[0] );
		msg.pushFloat( localPosition[1] );
		msg.pushFloat( localPosition[2] );

		environment->getSoundManager()->sendOSCMessage(msg);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Vector3f& SoundInstance::getPosition()
{
	return position;
}

void SoundInstance::setLocalPosition(Vector3f pos)
{
	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	localPosition = pos;
	position = environment->getSoundManager()->localToWorldPosition( localPosition );

	if( isPlaying() )
	{
		Message msg("/setObjectLoc");
		msg.pushInt32(instanceID);

		msg.pushFloat( position[0] );
		msg.pushFloat( position[1] );
		msg.pushFloat( position[2] );

		environment->getSoundManager()->sendOSCMessage(msg);

		Vector3f audioListener = environment->getUserPosition();
		float distanceToListener = Math::sqrt( Math::sqr(audioListener[0] - localPosition[0]) + Math::sqr(audioListener[3] - localPosition[3]) );
		float newVol = volume;
		if( rolloffMode == Sound::Rolloff::Linear )
		{
			newVol = ( 1 - ((distanceToListener - minRolloffDistance) / maxDistance)) * volume; //Linear rolloff
		}
		else if( rolloffMode == Sound::Rolloff::Logarithmic )
		{
			if( distanceToListener > 0 )
				newVol = minRolloffDistance * (maxDistance / Math::sqr(distanceToListener) );  // Logarithmic
		}
		if( newVol > volume )
			newVol = volume;

		setVolume( newVol );

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Vector3f& SoundInstance::getLocalPosition()
{
	return localPosition;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isEnvironmentSound()
{
	return environmentSound;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setEnvironmentSound(bool value)
{
	environmentSound = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setVolume(float value)
{
	if( isDone() )
		return;

	if( sound != NULL && value * sound->getVolumeScale() > 1 )
		this->volume = 1.0;
	else if( sound != NULL)
		this->volume =  value * sound->getVolumeScale();

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	if( isPlaying() )
	{
		Message msg("/setVol");
		msg.pushInt32(instanceID);
		msg.pushFloat(this->volume);


		environment->getSoundManager()->sendOSCMessage(msg);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getVolume()
{
	return volume;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::fade(float targetAmp, float envelopeDuration)
{
	if( isDone() )
		return;

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	if( isPlaying() )
	{
		if( stereoSound )
		{
			Message msg("/setSterVolEnv");
			msg.pushInt32(instanceID);

			msg.pushFloat(targetAmp); // Target amplitude
			msg.pushFloat(envelopeDuration); // Duration in seconds to reach new amplitude

			environment->getSoundManager()->sendOSCMessage(msg);
		}
		else
		{
			Message msg("/setVolEnv");
			msg.pushInt32(instanceID);

			msg.pushFloat(targetAmp); // Target amplitude
			msg.pushFloat(envelopeDuration); // Duration in seconds to reach new amplitude

			environment->getSoundManager()->sendOSCMessage(msg);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setWidth(float value)
{
	this->width = value;
	useEnvironmentParameters = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getWidth()
{
	return width;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setRoomSize(float value)
{
	if( isDone() )
		return;

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	this->roomSize = value;
	useEnvironmentParameters = false;
	
	if( isPlaying() )
	{
		Message msg("/setReverb");
		msg.pushInt32(instanceID);
		msg.pushFloat(wetness);
		msg.pushFloat(roomSize);

		environment->getSoundManager()->sendOSCMessage(msg);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getRoomSize()
{
	return roomSize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setWetness(float value)
{
	if( isDone() )
		return;

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	this->wetness = value;
	useEnvironmentParameters = false;
	
	if( isPlaying() )
	{
		Message msg("/setReverb");
		msg.pushInt32(instanceID);
		msg.pushFloat(wetness);
		msg.pushFloat(roomSize);

		environment->getSoundManager()->sendOSCMessage(msg);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getWetness()
{
	return wetness;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setReverb(float wetness, float roomSize)
{
	if( isDone() )
		return;

	if( environment->getSoundManager()->isDebugEnabled() )
		ofmsg("%1%: for instanceID: %2%", %__FUNCTION__ %instanceID);

	this->wetness = wetness;
	this->roomSize = roomSize;
	useEnvironmentParameters = false;
	
	if( isPlaying() )
	{
		Message msg("/setReverb");
		msg.pushInt32(instanceID);
		msg.pushFloat(wetness);
		msg.pushFloat(roomSize);

		environment->getSoundManager()->sendOSCMessage(msg);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setPitch(float value)
{
	this->pitch = value;
	if( isPlaying() )
	{
		if( stereoSound )
		{
			Message msg("/setStereoRate");
			msg.pushInt32(instanceID);
			msg.pushFloat(value);
			environment->getSoundManager()->sendOSCMessage(msg);
		}
		else
		{
			Message msg("/setMonoRate");
			msg.pushInt32(instanceID);
			msg.pushFloat(value);
			environment->getSoundManager()->sendOSCMessage(msg);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getPitch()
{
	return pitch;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setCurrentFrame(int value)
{
	if( isPlaying() )
	{
		if( stereoSound )
		{
			Message msg("/setStereoFrame");
			msg.pushInt32(instanceID);
			msg.pushInt32(value);
			environment->getSoundManager()->sendOSCMessage(msg);
		}
		else
		{
			Message msg("/setMonoFrame");
			msg.pushInt32(instanceID);
			msg.pushInt32(value);
			environment->getSoundManager()->sendOSCMessage(msg);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setMaxDistance(float value)
{
	this->maxDistance = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getMaxDistance()
{
	return maxDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setMinRolloffDistance(float value)
{
	this->minRolloffDistance = value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SoundInstance::getMinRolloffDistance()
{
	return minRolloffDistance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setDistanceRange(float min, float max)
{
	this->minRolloffDistance = min;
	this->maxDistance = max;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setNoRolloff()
{
	rolloffMode = Sound::Rolloff::None;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setLinearRolloff()
{
	rolloffMode = Sound::Rolloff::Linear;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setLogarthmicRolloff()
{
	rolloffMode = Sound::Rolloff::Logarithmic;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isRolloffEnabled()
{
	if( rolloffMode != Sound::Rolloff::None )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isRolloffLinear()
{
	if( rolloffMode == Sound::Rolloff::Linear )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundInstance::isRolloffLogarithmic()
{
	if( rolloffMode == Sound::Rolloff::Logarithmic )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundInstance::setSoundEnvironment(SoundEnvironment* environment)
{
	this->environment = environment;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundInstance::getID()
{
	return instanceID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundInstance::getBufferID()
{
	return sound->getBufferID();
}
