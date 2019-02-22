#pragma once
#include "../Lib.SecureStorage/ITrainManager.h"
#include "../Lib.Playlist/IPlaylist.h"
#include "../Lib.Base/timecode.h"
#include "cnlInfo.h"
#include "../Lib.BMRSetting/BMRServiceDefine.h"
#include "../frameToTCP/infoGPI.h"
#include "BroadcastInfoKeyDefine.h"
#include "../frameToTCP/infoPiP.h"
#include "ClientIdentityType.h"
#include "../Dll.FrameReceiver/FrameReceiverDefine.h"
using namespace std;

#define MAX_ID_LEN   NB_MAX_PROTECT_ID_SIZE
#define START_CMD_BYTES	0x49344449			// ID4I
#define STOP_CMD_BYTES	0x4F344449			// ID4O

namespace transportCmd
{
	enum class CmdType :uint8_t
	{
		e2e,
		play,
		idle,
		jump,
		preload,
		gang,
		clone,
		takeA,
		takeM,
		frameReceiverReply,
		Rtd,
		Gfx,
		setAProtection,
		delAProtection,
		delAllProtections,
		getAllProtections,
		createPlaylist,
		deletePlaylist,
		deleteAllPlaylist,
		insertElement,
		removeElement,
		removeAllElement,
		updateElement,
		serializePlaylist,
		preloadPlaylist,
		skipElement,
		nextElement,
		startImportTGA,
		importTGAFile,
		stopImportTGA,
		preloadTGA,
		liveTGA,
		audioConfig,
		changeAudioDelay,
		setAuxCam,
		getAuxCam,
		setAuxPRVmonitoring,
		getAuxPRVmonitoring,
		switchMixerSnapshot,
		SetLoop,
		SetRTDOnGPI,
		GetRTDOnGPI,
		getThumbnail,
		ImportClip,
		extendPlaylist,
		registerThumbnailCnl,
		SetGPIMode,
		AddWatchFolder,
		GetWatchFolder,
		RemoveWatchFolder,
		SetLimits,
		SetCustomInfo,
		GetCustomInfo,
		TakeAWithTransparency,
		RegisterBroadcastInfoKey,
		PiP,
		RegisterAudioMonitor,
		RegisterIdentity,
		GangEx,
		GetGPIMode,
		PlayEdit,
		SetGPIOnRTD,
		GetGPIOnRTD,
		EM_BMR_StartWork = 100,
		EM_BMR_StartRec,
		EM_BMR_StopRec,
		EM_BMR_EnableTimecode,
		EM_BMR_SelectAudioChannel,
		EM_BMR_EnableMonitorAudio,
		EM_BMR_SetCompression,
		EM_BMR_ExportClip,
		EM_BMR_SetStreamAddress,
		EM_BMR_SetEncodingMode,
		EM_BMR_SetEncodingFormat,
		EM_BMR_SetRTMPRetryTimes,
		EM_BMR_SetRTMPDealyBetweenRetry,
		EM_BMR_SetAudioGain,
		EM_BMR_SetBufferCount,
		EM_BMR_SetGopLength,
		EM_BMR_SelectCamera,
		EM_BMR_SetCameraName,
		EM_BMR_EjectDevice,
		EM_BMR_SetLogoPic,
		EM_BMR_EnableLogo,
		EM_BMR_SetLogoToFullSize,
		EM_BMR_SetLogoPosition,
		Export_Clip,
		Stop_Export,
		EM_BMR_AudioCountChange,
		SetAudioPresetId,
		EM_BMR_H264ExportType,
		EM_BMR_StartRecWithTimeCode,
		EM_BMR_StopRecWithTimeCode
	};

	enum GfxChannelType :uint8_t
	{
		gfx0,
		gfx1,
		gfx2,
		gfxChannelTypeMax,
	};

	enum RTDType :uint8_t
	{
		rtd1,
		rtd2,
		rtd3,
		rtd4,
	};

	enum PiPType :uint8_t
	{
		PiP_PGM,
		PiP_PRV,
		PiP_Max
	};

	enum DVEType :uint8_t
	{
		dve_MIX = 0,
		dve_WIPE_LR,
		dve_WIPE_RL,
	};

	enum AuxType : uint8_t
	{
		AUX1,
		AUX2,
		AUX_Max
	};

	enum AuxCamera :uint8_t
	{
		AUX_Cam_A = 0,
		AUX_Cam_B = 1,
		AUX_Cam_C = 2,
		AUX_Cam_D = 3,
		AUX_Cam_E = 4,
		AUX_Cam_F = 5,
		AUX_Cam_G = 6,
		AUX_Cam_H = 7,
		AUX_Cam_I = 8,
		AUX_Cam_J = 9,
		AUX_Cam_K = 10,
		AUX_Cam_None = 0xff
	};

	enum ThumbnailType :uint8_t
	{
		ThumbnailType_480_270_MJPEG,
		ThumbnailType_960_540_MJPEG,
	};

	enum MonitorAudioType :uint8_t
	{
		Monitor_ExternalAudio,
		Monitor_CameraReplayAudio,
		Monitor_CameraLiveAudio,
		Monitor_PGMAudio,
		Monitor_PRVAudio,
	};

	inline string getMonitorAudioTypeStr(MonitorAudioType _type)
	{
		switch (_type)
		{
		case Monitor_ExternalAudio:		return "ExternalAudio";
		case Monitor_CameraReplayAudio: return "ReplayAudio";
		case Monitor_CameraLiveAudio:	return "LiveAudio";
		case Monitor_PGMAudio:			return "PGMAudio";
		case Monitor_PRVAudio:			return "PRVAudio";
		default:						return "UnknownAudio";
		}
	}

#pragma pack(1)
	typedef struct SBaseCmd
	{
		uint32_t	startMark;
		CnlID		cnl;
		CmdType		cmdType;
	} sBaseCmd;

	typedef struct SBaseCmdRtn
	{
		uint32_t	sizeInByte;
		char		eventType;
		char		commandResult;//1: success 0:fail
	} sBaseCmdRtn;

	typedef struct TagInfo
	{
		int32_t tagSize;
		char 	tag[MAX_ID_LEN];
	}TagInfo_S;

	typedef struct IDInfo
	{
		int32_t     idSize;
		char 		id[MAX_ID_LEN];
	}IDInfo_S;

	struct CreateProtectionPara
	{
		TMprotectInfo  TMprotectInfo;
		TagInfo  tag;
	};

	struct DeleteProtectionPara
	{
		IDInfo   id;
		TagInfo  tag;
	};

	struct GetAllProtectionsPara
	{
		struct TagInfo tag;
	};

	struct DelAllProtectionsPara
	{
		struct TagInfo tag;
	};

	struct sE2EParam
	{
		CnlID camera;
	};

	struct sSpeedParam
	{
		int32_t speedN;
		int32_t speedD;
	};

	typedef struct SJumpParam
	{
		int32_t offset;
	} sJumpParam;

	struct sPreloadParam
	{
		uint64_t position;
	};

	struct sGangParam
	{
		char group;
	};

	struct sGangExParam
	{
		struct PlayerGangParam
		{
			CnlID  playerID;
			char group;
		};

		int32_t count;
		PlayerGangParam* pParamArray;
	};

	typedef struct SCloneParam
	{
		CnlID cnlToClone;
		bool  bCloneCamera;
	} sCloneParam;

	typedef struct STakeAutoParam
	{
		CnlID cnlToTake;
		DVEType type;
		int32_t dur;
		int32_t threshold;
	} sTakeAutoParam;

	struct TakeAutoWithTransparencyParam
	{
		CnlID cnlToTake;
		DVEType type;
		int32_t dur;
		uint8_t* transparencyArray;
	};

	typedef struct SLoopParam
	{
		uint8_t mode;
		int32_t count;
		uint32_t tagSize;
		char  tag[MAX_ID_LEN];
	} sLoopParam;

	struct SetCustomInfoParam
	{
		uint32_t keySize;
		uint32_t valueSize;
		char  key[MAX_ID_LEN];
		char* value;
	};

	struct GetCustomInfoParam
	{
		uint32_t keySize;
		uint32_t tagSize;
		char  key[MAX_ID_LEN];
		char  tag[MAX_ID_LEN];
	};

	typedef struct SLimitParam
	{
		bool isInRelative;
		uint64_t limitIn;
		bool isOutRelative;
		uint64_t limitOut;
		uint32_t tagSize;
		char  tag[MAX_ID_LEN];
	} sLimitParam;

	typedef struct STakeManualParam
	{
		CnlID cnlToTake;
		DVEType type;
		int32_t num;
		int32_t den;
	} sTakeManualParam;

	typedef struct SRtdParam
	{
		RTDType type;
	} sRtdParam;

	struct sPiPParam
	{
		PiPType type;
		bool	enable;
		uint8_t	nbCamera;
		uint32_t	tagSize;
		backgroundInfo bgInfo;
		PiPOverlayInfo* overlayInfo;
		char  tag[MAX_ID_LEN];
	};

	typedef struct SGfxParam
	{
		GfxChannelType gfxChannel;
		bool isEnableGfx;
		int32_t fadeInDuration;
		int32_t fadeOutDuration;
		int32_t loopIn;
		int32_t loopOut;
		int32_t loopCnt;
		int32_t	delayFrame;
	} sGfxParam;

	typedef struct SCreatePlaylistParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		char  playlistId[MAX_ID_LEN];
		char  tag[MAX_ID_LEN];
	} sCreatePlaylistParam;

	typedef struct SDeletePlaylistParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		char  playlistId[MAX_ID_LEN];
		char  tag[MAX_ID_LEN];
	} sDeletePlaylistParam;

	typedef struct SInsertElementParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		uint32_t elementIdSize;
		uint32_t previousElementIdSize;
		uint8_t camera;
		int32_t speedN;
		int32_t speedD;
		uint64_t in;
		uint64_t out;
		uint64_t video_effect_duration;
		uint64_t audio_effect_duration;
		VideoEffectType video_effect_type;
		AudioEffectType audio_effect_type;
		char playlistId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
		char elementId[MAX_ID_LEN];
		char previousElementId[MAX_ID_LEN];
	} sInsertElementParam;

	typedef struct SRemoveElementParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		uint32_t elementIdSize;
		char playlistId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
		char elementId[MAX_ID_LEN];
	} sRemoveElementParam;

	typedef struct SRemoveAllElementParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		char playlistId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	} sRemoveAllElementParam;

	typedef struct SDeleteAllPlaylistParam
	{
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	} sDeleteAllPlaylistParam;

	typedef struct SSerializePlaylistParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		char playlistId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	} sSerializePlaylistParam;

	typedef struct SUpdateElementParam
	{
		uint32_t playlistIdSize;
		uint32_t tagSize;
		uint32_t elementIdSize;
		uint8_t camera;
		int32_t speedN;
		int32_t speedD;
		uint64_t in;
		uint64_t out;
		uint64_t video_effect_duration;
		uint64_t audio_effect_duration;
		VideoEffectType video_effect_type;
		AudioEffectType audio_effect_type;
		char playlistId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
		char elementId[MAX_ID_LEN];
	} sUpdateElementParam;

	typedef struct SPreloadPlaylistParam
	{
		uint32_t playlistIdSize;
		uint32_t elementIdSize;
		uint64_t field;
		char playlistId[MAX_ID_LEN];
		char elementId[MAX_ID_LEN];
	} sPreloadPlaylistParam;

	struct StartImportTGA
	{
		uint32_t ingestIdSize;
		uint32_t tagSize;
		uint32_t trainType;
		uint32_t trainId;
		uint32_t sourceMedia;
		char ingestId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	};

	struct ImportTGAFile
	{
		uint32_t ingestIdSize;
		uint32_t tgaIdSize;
		uint32_t tagSize;
		uint32_t frameSize;
		char ingestId[MAX_ID_LEN];
		char tgaId[MAX_ID_LEN];
		char* frame;
		char tag[MAX_ID_LEN];
	};

	struct StopImportTGA
	{
		uint32_t ingestIdSize;
		uint32_t tagSize;
		char ingestId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	};

	struct PreloadTGA
	{
		char cnl;
		uint32_t ingestIdSize;
		uint32_t tagSize;
		char ingestId[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	};

	struct GetThumbnailParam
	{
		ThumbnailType type;
		uint64_t field;
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	};

	struct ExtendPlaylistParam
	{
		bool enable;
	};

	struct LiveTGAFileParam
	{
		uint32_t tagSize;
		uint32_t frameSize;
		char tag[MAX_ID_LEN];
		char* frame;
	};

	struct changeAudioDelayParam
	{
		uint32_t resetCnt;
	};

	struct SetAuxCamParam
	{
		AuxType auxType;
		AuxCamera auxCamera;
	};

	struct GetAuxCamParam
	{
		AuxType auxType;
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	};

	struct SetAuxPRVmonitoringParam
	{
		AuxCamera auxCamera;
	};

	struct GetAuxPRVmonitoringParam
	{
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	};

	struct AudioConfigParam
	{
		uint32_t  xmlLen;    //in bytes
		char*  xmlContent;
	};

	struct SwitchMixerSnapshotParam
	{
		uint8_t	midiCnlID;
		uint8_t    mixerSnapshotID;
	};

	struct ImportClipParam
	{
		uint32_t pathLen;
		uint32_t tagSize;
		char path[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	};

	struct SetGPIModeParam
	{
		GPIMode mode[MAX_GPI_PORT];
		GPI_CAM_MAP map[MAX_GPI_PORT];
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	};
	struct GetGPIMode
	{
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	};
	struct AddWatchFolderParam
	{
		uint32_t pathLen;
		uint32_t tagSize;
		char path[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	};

	struct GetWatchFolderParam
	{
		uint32_t tagSize;
		char tag[MAX_ID_LEN];
	};

	struct RemoveWatchFolderParam
	{
		uint32_t pathLen;
		uint32_t tagSize;
		char path[MAX_ID_LEN];
		char tag[MAX_ID_LEN];
	};

	struct RegisterAudioMonitorParam
	{
		MonitorAudioType audioLeftType;
		MonitorAudioType audioRightType;
		int32_t audioLeft;
		int32_t audioRight;
	};

	struct SBMR_StartRec
	{
		CamID   id;
	};

	struct SBMR_StopRec
	{
		CamID   id;
	};

	struct SBMR_StartRecWithTimeCode
	{
		CamID   id;
		Timecode	tc;
	};

	struct SBMR_StopRecWithTimeCode
	{
		CamID   id;
		Timecode	tc;
	};

	struct SBMR_EnableTimecode
	{
		CamID   id;
		bool    tcOn;
	};

	struct SBMR_SelectAudioChannel
	{
		CamID   id;
		uint8_t	selectNum;
		uint8_t	audioSrcChannel;
		uint8_t	audioDstChannel;
		bool    isLow;
		ExportAudioType exportAudioType;
	};

	struct SBMR_EnableMonitorAudio
	{
		CamID   id;
		bool	bEnable;
	};

	struct SBMR_SetCompression
	{
		CamID   id;
		uint32_t   dwCompressionRate;
		bool	bCustom;
	};

	struct SBMR_ExportClip
	{
		CamID		id;
		Timecode	tcIn;
		Timecode	tcOut;
		ExportFileType exportType;
		char        szFileName[MAX_PATH];
	};

	struct SBMR_SetStreamAddress
	{
		CamID			id;
		BMRNetdriveType type;
		char			netdriverindex;
		char			address[MAX_PATH];
	};

	struct SBMR_SetEncodingMode
	{
		CamID   id;
		bool	bCabacMode;
	};

	struct SBMR_SetEncodingFormat
	{
		CamID   id;
		BMREncoderType	bmrEncoderType;
	};

	struct SBMR_SetRTMPRetryTimes
	{
		CamID   id;
		uint32_t   dwRetryTimes;
	};

	struct SBMR_SetRTMPDealyBetweenRetry
	{
		CamID   id;
		uint32_t   dwDealy;
	};

	struct SBMR_SetAudioGain
	{
		CamID   id;
		uint32_t   dwAudioGain;
	};

	struct SBMR_SetBufferCount
	{
		CamID   id;
		uint32_t   dwBufferCount;
	};

	struct SBMR_SetGopLength
	{
		CamID   id;
		uint32_t   dwGopLength;
	};

	struct SBMR_SelectCamera
	{
		CamID   id;
		char	netdriveID;
		ExportFileType exportType;
		bool    bSelect;
	};

	struct SBMR_SetCameraName
	{
		CamID   id;
		char    name[MAX_PATH];
	};

	struct SBMR_EjectDevice
	{
		char netdriveID;
	};

	struct SBMR_SetLogoPic
	{
		CamID id;
		uint32_t tagSize;
		uint32_t picSize;
		char tag[MAX_ID_LEN];
		char* pic;
	};

	struct SBMR_EnableLogo
	{
		CamID id;
		bool isEnabled;
	};

	struct SBMR_SetLogoToFullSize
	{
		CamID id;
		bool isEnabled;
	};

	struct SBMR_SetLogoPosition
	{
		CamID id;
		LogoPosition position;
		uint32_t dwXAxis;
		uint32_t dwYAxis;
	};

	struct stuExport_Clip
	{
		CamID id;
		unsigned char	netDriveID; //
		ExportFileType  filetype;	//
		uint64_t	startFrameID;		//[8 uint8_t]startFrameID == -1 means export from the current press start.
		uint64_t	stopFrameID;		//[8 uint8_t]stopFrameID == -1 means growing
		uint32_t   dwGopValue;			//need when the format is H264
		uint32_t   dwCompressionRate;	//need when the format is H264
		ExportAudioType	 exportAudioType;
		bool    bWritetoClientEnd;	//
		uint32_t   dwDataPortA;		//
		uint32_t   dwDataPortV;		//
		uint32_t   dwReserverd[8];	    //32 bytes reserved
		uint32_t   audioCount;			//audio channel count
		uint32_t	pathLen;			//[4 uint8_t]
		uint32_t	taskGUIDLen;		//[4 uint8_t]
		uint32_t	clipProtectIDLen;	//[4 uint8_t]
		char	audioFileMap[16];	//[taskGUIDLen uint8_t]
		char	path[MAX_PATH]; 	//[pathLen uint8_t]
		char	taskGUID[MAX_PATH];	//[taskGUIDLen uint8_t]
		char	clipProtectID[MAX_PATH];	//[clipProtectIDLen uint8_t]
	};

	struct stuStop_Export
	{
		CamID id;
		uint32_t	taskGUIDLen;		//[4 uint8_t]
		char	taskGUID[MAX_PATH];	//[taskGUIDLen uint8_t]
	};

	struct SBMR_AudioCountChange
	{
		CamID	id;
		uint8_t	selectNum;
		bool    isLow;
	};
	struct SBMR_ExportH264FileType
	{
		CamID	id; //
		ExportFileType exportH264FileType;
	};
	typedef struct SetAudioPreset
	{
		uint8_t   audioPresetId;
	} SetAudioPresetCmd;

	struct RegisterBroadcastInfoKey
	{
		uint16_t			nbOfKey;
		uint16_t 			tagSize;
		BroadcastInfoKey*	keyArray;
		char				tag[MAX_PATH];
	};

	struct RTDOnGPIParam
	{
		bool enable;
	};

	struct GPIOnRTDParam
	{
		bool enable;
	};

	struct RegisterIdentityParam
	{
		ClientIdentityType	type;
		uint32_t 				identityStringSize;
		char*				identityString;
	};

	struct RegisterThumbnailCnl
	{
		char	 idArray[RegisterCnlMaxLen] = { 0 };
		uint64_t tag;
	};

	struct FrameReceiverReplyParam
	{
		uint64_t time_stamp;
		debug_info client_debug_info;
	};

	typedef struct SCmd
	{
		sBaseCmd base;

		union
		{
			sE2EParam e2e;
			sSpeedParam speed;
			sJumpParam jump;
			sPreloadParam preload;
			sGangParam gang;
			sGangExParam gangEx;
			sCloneParam clone;
			sTakeAutoParam takeA;
			TakeAutoWithTransparencyParam takeAutoWithTransparency;
			sTakeManualParam takeM;
			sRtdParam rtd;
			sGfxParam gfx;
			sLoopParam setLoop;
			sLimitParam setLimit;
			sCreatePlaylistParam createPlaylist;
			sDeletePlaylistParam deletePlaylist;
			sDeleteAllPlaylistParam deleteAllPlaylist;
			sInsertElementParam insertElement;
			sRemoveElementParam removeElement;
			SRemoveAllElementParam removeAllElement;
			sUpdateElementParam updateElement;
			sSerializePlaylistParam serializePlaylist;
			sPreloadPlaylistParam preloadPlaylist;
			CreateProtectionPara createAProtectionPara;
			DeleteProtectionPara  delAProtectionPara;
			DelAllProtectionsPara delAllProtectionsPara;
			GetAllProtectionsPara getAllProtectionsPara;
			StartImportTGA startImportTGAPara;
			ImportTGAFile importTGAFilePara;
			StopImportTGA stopImportTGAPara;
			PreloadTGA preloadTgaPara;
			LiveTGAFileParam liveTGAPara;
			AudioConfigParam  audioConfigPara;
			changeAudioDelayParam changeAudioDelayPara;
			SetAuxCamParam setCamAuxPara;
			GetAuxCamParam getCamAuxPara;
			SetAuxPRVmonitoringParam setAuxPRVMonitoring;
			GetAuxPRVmonitoringParam getAuxPRVMonitoring;
			SwitchMixerSnapshotParam switchMixerSnapshotCmd;
			GetThumbnailParam getThumbnailCmd;
			ImportClipParam	importClipParam;
			ExtendPlaylistParam extendPlaylistParam;
			SetGPIModeParam setGPImodeParam;
			AddWatchFolderParam addWatchFolderParam;
			GetWatchFolderParam getWatchFolderParam;
			RemoveWatchFolderParam removeWatchFolderParam;
			SetCustomInfoParam setCustomInfoParam;
			GetCustomInfoParam getCustomInfoParam;
			RegisterBroadcastInfoKey registerInfo;
			sPiPParam pipParam;
			RegisterAudioMonitorParam audioMonitorParam;
			RegisterIdentityParam registerIdentityParam;
			SetAudioPresetCmd  stSetAudioPresetCmd;
			stuExport_Clip exportClip;
			stuStop_Export stopExport;
			RTDOnGPIParam	rtdOnGPIParam;
			GPIOnRTDParam	gpiOnRTDParam;
			GetGPIMode		getGPIMode;
			sSpeedParam		playEdit;//when replay playlist with this cmd, never use element's speed
			FrameReceiverReplyParam frameReceiverReplyCmd;
			//BMR Commands.
			SBMR_StartRec sbmrStartRec;
			SBMR_StopRec  sbmrStopRec;
			SBMR_EnableTimecode  sbmrEnableTimecode;
			SBMR_SelectAudioChannel  sbmrSelectAudioChannel;
			SBMR_EnableMonitorAudio  sbmrEnableMonitorAudio;
			SBMR_SetCompression  sbmrSetCompression;
			SBMR_ExportClip  sbmrExportClip;
			SBMR_SetStreamAddress  sbmrSetStreamAddress;
			SBMR_SetEncodingMode  sbmrSetEncodingMode;
			SBMR_SetEncodingFormat  sbmrSetEncodingFormat;
			SBMR_SetRTMPRetryTimes  sbmrSetRTMPRetryTimes;
			SBMR_SetRTMPDealyBetweenRetry  sbmrSetRTMPDealyBetweenRetry;
			SBMR_SetAudioGain  sbmrSetAudioGain;
			SBMR_SetBufferCount  sbmrSetBufferCount;
			SBMR_SetGopLength  sbmrSetGopLength;
			SBMR_SelectCamera  sbmrselectCamera;
			SBMR_SetCameraName sbmrSetCameraName;
			SBMR_EjectDevice sbmrEjectDevice;
			SBMR_SetLogoPic sbmrSetLogoPic;
			SBMR_SetLogoPosition sbmrSetLogoPosition;
			SBMR_SetLogoToFullSize sbmrSetLogoToFullSize;
			SBMR_EnableLogo sbmrEnableLogo;
			SBMR_AudioCountChange stuAudioCnt;
			SBMR_ExportH264FileType  stExportH264FileTypeCmd;
			SBMR_StartRecWithTimeCode sbmrStartRecWithTC;
			SBMR_StopRecWithTimeCode  sbmrStopRecWithTC;
			RegisterThumbnailCnl registerThumbnailCnlCmd;
		};

		SCmd()
		{
			memset(this, 0, sizeof(SCmd));
		}
	} sCmd;
#pragma pack()
}
