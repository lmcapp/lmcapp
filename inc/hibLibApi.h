// hibLibApi.h

//////////////////////////////////////////////////////////////////////////////////////////
//
// Xerox Head Interface Board (HIB) Application Programmer's Interface
//
//		This header file defines the entry functions used by applications that
//		make use of the HIB API library.
//
//		?015 Xerox Corporation, All Rights Reserved
// 
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef HIB_LIB_API_H	// header guard prevents multiple def attempts
#define HIB_LIB_API_H


#ifdef __cplusplus	// Prevent C++ name mangling to assure portability
extern "C" {
#endif

	// Add optional prefix to function prototypes based on defines.
#ifdef DLL_IMPORT
#define API __declspec(dllimport)
#else
#ifdef DLL_EXPORT
#define API __declspec(dllexport)
#else
#define API
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//
//	Type definition for hibStatus_t, the return type used by many API functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
typedef enum hibStatusTag
{
	hibSuccess = 0,
	hibFailure = -1,			// generic failure
	hibNoBoardsFound = -2,		// Can't find an interface board attached to the system
	hibBoardNotAvailable = -3,	// e.g., requested use of a board that wasn't discovered.
	hibHeadInitNotComplete = -4,// Known head type not connected, or head nvram not read/decoded
	hibMemoryError = -5,		// Memory allocation error in the library
	hibDriverMemoryError = -6,	// Memory allocation error in the driver
	hibWaveampFaultError = -7,	// Waveamp fault (or wave amp is not connected)
	hibNotApplicable = -8,		// Not applicable for hib/head type or situation
	hibWaveformClipped = -9,	// Waveform voltage clipped at max allowed.
	hibWaveCalFailure = -10,	// waveCal failed
	hibBiasVoltageShort = -11,	// Unable to apply waveform bias.
	hibDataNotAvailable = -12,	// Data not available.
	hibMotorStallDetected = -13,// Stitch/Roll adjust stall error detected.
	hibMotorShortDetected = -14,// Stitch/Roll adjust short error detected.
	hibMotorOpenDetected = -15, // Stitch/Roll adjust open error detected.
	hibFileAlreadyExists = -16, // File to be created already exists.
	hibWaitTimeout = -17		// Timeout exceeded during wait for event.
} hibStatus_t;

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Hardware Initialization and Configuration Functions
//					(and their related type definitions)
// 
//////////////////////////////////////////////////////////////////////////////////////////
API hibStatus_t hibInitAllBoards(int *pnNumBoards, bool bMasterPcFlag = true);

typedef enum hibBoardStateTag  	// Typedef describing various head interface board states...
{
	// HIB & head states, in descending order of print readiness
	hibReady = 0,					// Hib & Head seem healthy, head nvram was read & decoded
	hibHeadNvramNotDecoded = -1,	// Head board was found, but could read and/or decode nvram image
	hibHeadNotFound = -2,			// Can't find a head driver board attached to the HIB
	hibUnknownState = -3,			// Haven't checked yet, or can't successfully determine state.
	hibBoardError = -4				// Generic error
} hibBoardState_t;

API hibStatus_t hibGetStatus(int nHibChainNum, hibBoardState_t *pBoardState);

API hibStatus_t hibCloseAllBoards(void);

// Head types.
typedef enum _hibHeadType_t
{
	hibUnknownHead = -1,
	hibWorkhorseHead = 0,
	hibMSeriesHead,
	hibTSeriesHead
} hibHeadType_t;

// Typdefs related to setting up the dot clock and encoder parameters
typedef enum { hibAutoFire, hibQuadEncoder, hibExternalDotClock, hibQuadEncoderPos } hibDotclockType_t;
typedef struct
{
	hibDotclockType_t type;				// User can select from several dot clock schemes

	// For type hibAutoFire, set these...
	float		fAutoFireFreqHz;
	bool		bAutoFireFromMasterHib;	// true: master hib generates dot clock for all,

	// For type hibQuadEncoderInput, set these
	float		fEncoderResolution;		// Quad encoder res expressed as counts per inch of paper
	unsigned	uPrintResDpi;			// Print resolution


	// Optionally use a page start signal
	bool		bEnablePageStart;
	bool		bEnablePageStop;	// if true, we stop dots on falling edge of page start

	// For test purposes, 
	bool		bWaveAmpPresent;	// Set false to allow testing w/o a wave amp
	bool		bHeadReadyOverride;	// Set true to allow testing w/o a printhead

} hibDotClockDef_t;

API hibStatus_t hibSetupAllDotclocks(hibDotClockDef_t *pDotClockDef);	// Set dot clock config. for all HIBs

API hibStatus_t hibSetYOffset(int nHibChainNum, float fYOffsetInDots);
API hibStatus_t hibConfigPage(int nHibChainNum, float fPageActiveOffsetInDots, float fYOffsetInDots, int nPageLength, int nPageChainDriveMode);
API hibStatus_t hibSetPrintStartPos(int nHibChainNum, float fPageStartPosNonQuadEncoderCounts);
API hibStatus_t hibSetEncoderPos(int nHibChainNum, int nEncoderPosQuadratureCounts);
API hibStatus_t hibGetEncoderPos(int nHibChainNum, int *pnEncoderPosQuadratureCounts);

// HIB and head version info.
typedef struct _HIB_VERSION_INFO
{
	unsigned int version;
	unsigned int buildDate;
	unsigned int headType;
	unsigned int headVersion;
	unsigned int headBuildDate;
} HIB_VERSION_INFO;

API hibStatus_t hibGetVersionInfo(int nHibChainNum, HIB_VERSION_INFO *pHibVersionInfo);
API hibStatus_t hibGetHibLibVersion(int *pVerMajor, int *pVerMinor, char **ppBuildDate, char **ppBuildTime, char **ppBuildConfig);
API hibStatus_t hibGetDriverVersion(int *pVerMajor, int *pVerMinor, char **ppBuildDate, char **ppBuildTime, char **ppBuildConfig);
//////////////////////////////////////////////////////////////////////////////////////////
//
//				Thermal Status and Control Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
API hibStatus_t hibSetThermalSetpoint(int nHibChainNum, int nWaveNum, int nHeaterNum, float fSetPointTempC);
API hibStatus_t hibGetThermalSetpoint(int nHibChainNum, int nWaveNum, int nHeaterNum, float *pfSetPointTempC);
API hibStatus_t hibGetHeaterTemp(int nHibChainNum, int nHeaterNum, float *pfHeaterTempC);

API hibStatus_t hibGetWaveAmpTemp(int nHibChainNum, float *pfWaTemp, float *pfWaTempLimit);

// M/T Series Temperature analog output config structure.
typedef struct
{
	float	fResCenterTemp;
	float	fResScaleDegPerVolt;
	float	fJetLeftCenterTemp;
	float	fJetLeftScaleDegPerVolt;
	float	fJetRightCenterTemp;
	float	fJetRightScaleDegPerVolt;
} hibTempAnalogOutput_t;

API hibStatus_t hibSetTempAnalogOutputs(int nHibChainNum, hibTempAnalogOutput_t *pTempAnalogOutput);
API hibStatus_t hibGetTempAnalogOutputs(int nHibChainNum, hibTempAnalogOutput_t *pTempAnalogOutput);

// M/T Series thermistor config structure. Three temp/resistance points and pullup resistance.
typedef struct
{
	float	fTemp1;
	float	fTemp2;
	float	fTemp3;
	float	fResistance1;
	float	fResistance2;
	float	fResistance3;
	float	fPullupResistance;
} hibThermistorConfig_t;

API hibStatus_t hibSetThermistorType(int nHibChainNum, int nHeaterNum, hibThermistorConfig_t *pThermistorConfig);
API hibStatus_t hibGetThermistorType(int nHibChainNum, int nHeaterNum, hibThermistorConfig_t *pThermistorConfig);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Ink levels and ink load control.
// 
//////////////////////////////////////////////////////////////////////////////////////////

// M/T Series ink level sense thermistor config structure. Three temp/resistance points and pullup resistance.
// Also level sense threshold pullup/pulldown resistance values.
typedef struct
{
	float	fTemp1;
	float	fTemp2;
	float	fTemp3;
	float	fResistance1;
	float	fResistance2;
	float	fResistance3;
	float	fPullupResistance;
	float	fThresholdPullupResistance;
	float	fThresholdPulldownResistance;
	float	fInkTempOffset;			// Set to -1 for optical level sense.
	float	fInkCenterTemp;
	float	fInkScaleFactor;
} hibLevelSenseConfig_t;

API hibStatus_t hibSetInkLevelSenseConfig(int nHibChainNum, hibLevelSenseConfig_t *pLevelSenseConfig);
API hibStatus_t hibGetInkLevelSenseConfig(int nHibChainNum, hibLevelSenseConfig_t *pLevelSenseConfig);

API hibStatus_t hibGetHeadInkLevels(int nHibChainNum, int &nIl1, int &nIl2, int &nIl3, int &nIl4);

API hibStatus_t hibGetHeadInkPressure(int nHibChainNum, int *pPressureChan1, int *pPressureChan2);


//////////////////////////////////////////////////////////////////////////////////////////
//
//				Head NVRAM Access Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
#define HIB_JET_IS_VIRTUAL 0xfffe
#define HIB_MASK_JET 0xffff

typedef struct _headHcdMisc_t
{
	unsigned char headSn[20];
	hibHeadType_t headType;
	int numJets;
	int numJetsPerInch;
	int numRows;
	int numWaveforms;
	int gsWaveformType;
	int smallDropWfm;
	int largeDropWfm;
	int numColors;
	int numArrays;
	int arrayColorIdx[4];            // Max 4 arrays per head.
	int arrayColumnIdx[4];           // Max 4 arrays per head.
	int numBitsPerPixel;
	int numImageCols;
	int numThermalChannels;
} headHcdMisc_t;

API hibStatus_t hibShowHeadHcd(int nHibNum, char *pShowParams);
API hibStatus_t hibGetImgColOffsets(int nHibChainNum, int nYDpi, bool bIncludeJetDelays, bool bMaskBadJets, int **ppImgYOffsets, bool bRevPrint = false);
API hibStatus_t hibLoadShadowHcdFromHead(int nHibChainNum);				// Read & decode the Hcd image

API hibStatus_t hibGetShadowHcdPtr(int nHibChainNum, unsigned char * &pHcdImage, int &nNumBytes);
API hibStatus_t hibDumpShadowHcdToFile(int nHibChainNum, char * filename);
API hibStatus_t hibGetHeadHcdPtr(int nHibChainNum, unsigned char * &pHcdImage, int &nNumBytes);
API hibStatus_t hibDumpHeadHcdToFile(int nHibChainNum, char * filename);
API hibStatus_t hibLoadShadowHcdFromBuffer(int nHibChainNum, unsigned char *pHcdImage);
API hibStatus_t hibLoadShadowHcdFromFile(int nHibChainNum, char *filename);
API hibStatus_t hibCopyHeadHcdToBuffer(int nHibChainNum, int nByteOffset, int nNumBytes, unsigned char *pRtnBuf);

API hibStatus_t hibGetRowSpacing(int nHibChainNum, int nNumRows, int *pRowSpacing);
API hibStatus_t hibGetRowOrder(int nHibChainNum, int &nNumRows, int * &pRowOrder);
API hibStatus_t hibGetJetMaskList(int nHibChainNum, int nNumVals, int *pJetMaskList);
API hibStatus_t hibGetYdelays(int nHibChainNum, int nWaveNum, int nNumDelays, char *pYdelays);
API hibStatus_t hibGetNormVals(int nHibChainNum, int nWaveNum, int nNumNorms, char *pNormVals, int nNormSet = 1);
API hibStatus_t hibGetHeadMisc(int nHibChainNum, headHcdMisc_t *pMiscInfo);
API hibStatus_t hibGetThermalChanNames(int nHibChainNum, int &nNumThermalChans, char ** &pThermalChanNames);

API hibStatus_t hibSetRowSpacing(int nHibChainNum, int nNumRows, int *pRowSpacing);
API hibStatus_t hibLoadJetMaskList(int nHibChainNum, int nNumVals, int *pJetMaskList);
API hibStatus_t hibSetJetMask(int nHibChainNum, int nJet, int nMaskState);
API hibStatus_t hibLoadYdelays(int nHibChainNum, int nWaveNum, int nNumDelays, char *pYdelays);
API hibStatus_t hibSetJetYdelay(int nHibChainNum, int nWaveNum, int nJet, int nDelay);
API hibStatus_t hibIgnoreYdelays(int nHibChainNum, int nIgnoreState);
API hibStatus_t hibLoadNormVals(int nHibChainNum, int nWaveNum, int nNumNorms, char *pNormVals, int nNormSet = 1);
API hibStatus_t hibSetJetNorm(int nHibChainNum, int nWaveNum, int nJet, int nNorm, int nNormSet = 1);

API hibStatus_t hibSetFireRate(int nHibChainNum, int nWaveNum, unsigned int nFireRateHz);
API hibStatus_t hibGetFireRate(int nHibChainNum, int nWaveNum, unsigned int * pnFireRateHz);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Solenoid and Motor Control Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
API hibStatus_t	hibSetSolenoidPwmDuty(int nHibChainNum, int nSolNum, int nDutyPercent);
API hibStatus_t	hibSetSolenoidOnTime(int nHibChainNum, int nSolNum, float fOnTimeSecs);
API hibStatus_t	hibGetSolenoidOnTime(int nHibChainNum, int nSolNum, float &fOnTimeSecs);
API hibStatus_t	hibSetMotorCurrent(int nHibChainNum, int nMotorNum, float fCurrentAmps);
API hibStatus_t	hibSetMotorStallThreshold(int nHibChainNum, int nMotorNum, int nStallThreshold);
API hibStatus_t	hibSetMotorVelocity(int nHibChainNum, int nMotorNum, float fVelStepsPerSec);
API hibStatus_t	hibGetMotorVelocity(int nHibChainNum, int nMotorNum, float &fVelStepsPerSec);
API hibStatus_t	hibSetMotorTime(int nHibChainNum, int nMotorNum, float fRunTimeSec);
API hibStatus_t	hibSetMotorPos(int nHibChainNum, int nMotorNum, float fPosSteps);
API hibStatus_t	hibGetMotorPos(int nHibChainNum, int nMotorNum, float &fPosSteps);
API hibStatus_t	hibClearMotorStallCount(int nHibChainNum, int nMotorNum);
API hibStatus_t	hibGetMotorStallCount(int nHibChainNum, int nMotorNum, int &nStallCount);

API hibStatus_t	hibAdjustStitch(int nHibChainNum, int nDistUm);
API hibStatus_t	hibAdjustRoll(int nHibChainNum, int nRollUrad);
API hibStatus_t	hibSetStitchRollBacklash(int nStitchBacklashUm, int nRollBacklashUrad);
API hibStatus_t	hibSetStitchRollScale(float fStitchDistUmPerStep, float fRollDistUradPerStep);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Image Transfer Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
typedef void(*imageXferCallback_t)(int nHibChainNum, unsigned char * &pImageData, int *pNumBytes, void *pUserData);
API hibStatus_t hibSetupImageTransfer(int nHibChainNum, imageXferCallback_t imageXferCallback, void *pUserData);

typedef void(*imageFreeMemCallback_t)(int nHibChainNum, unsigned char *pUserImageData, void *pUserMemFreeData);
API hibStatus_t hibSetFreeMemoryCallback(int nHibChainNum, imageFreeMemCallback_t imageFreeMemCallback, void *pUserData);

API hibStatus_t hibEnablePrinting(void);	// Image transfer callbacks begin.  Enable dot clocks on master hib
API hibStatus_t hibWaitForImageTransferComplete(int nHibChainNum);
API hibStatus_t hibWaitForImageTransferCompleteWto(int nHibChainNum, int nTimeoutMs);

API hibStatus_t hibCancelImageTransfer(int nHibChainNum, bool bBlock);	// Cancel a pending image data transfer request

// For printBar based packed image data.
typedef struct packedCbImg_t
{
	unsigned int * pImgBuf[4];       // One pointer for each of the head's color planes.
	int imgLengthPixels;
	int imgWidthPixels;
	int bitsPerPixel;
	int imgXResDpi;
	int imgYResDpi;
	bool imgReversed;
} packedCbImg_t;

typedef void(*imageXferCallbackPacked_t)(int nPrintBarNum, packedCbImg_t *pImageData, void *pUserData);
API hibStatus_t hibSetupPackedImageTransfer(int nPrintBarNum, imageXferCallbackPacked_t imageXferCallback, void *pUserData);

typedef void(*imageFreeMemCallbackPacked_t)(int nPrintBarNum, packedCbImg_t *pImageData, void *pUserMemFreeData);
API hibStatus_t hibSetFreePackedMemoryCallback(int nPrintBarNum, imageFreeMemCallbackPacked_t imageFreeMemCallback, void *pUserData);

typedef struct bmpCbImg_t
{
	char * bmpFilename[4];       // One bmp file for each of the head's color planes.
	int bmpXResOverride;
	int bmpYResOverride;
	bool imgReversed;
} bmpCbImg_t;

typedef void(*imageXferCallbackBmp_t)(int nPrintBarNum, bmpCbImg_t *pBmpData, void *pUserData);
API hibStatus_t hibSetupBmpImageTransfer(int nPrintBarNum, imageXferCallbackBmp_t imageXferCallback, void *pUserData);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Waveform Adjustments and Customization Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
/* Knot polarity designators */
typedef enum {
	VPPx,
	VSSx
} hibWavePolarity_t;
typedef struct {
	float				timeUs;
	float				voltageV;
	hibWavePolarity_t	drive;
	hibWavePolarity_t	connect;
	bool				scalable;
	bool				reference;
	int					normRegion;
} hibWaveKnot_t;

typedef struct {
	unsigned		cameraDelay15nsClks;
	unsigned		strobeDelay15nsClks;
	unsigned		strobeDelta15nsClks;
	unsigned		strobeHoldoff15nsClks;
	unsigned		cameraWidth15nsClks;
	unsigned		strobeWidth15nsClks;
	unsigned		strobeLatencyDotClks;
} hibCameraStrobe_t;

API int hibWaveformMaxKnotCount(int nHibChainNum);

// Adjust the waveform voltage
API hibStatus_t hibAdjustWaveformVoltage(int nHibChainNum, int nWaveNum, float fDeltaVoltage);

// Load waveform from a waveform text file.
API hibStatus_t hibLoadWaveform(int nHibChainNum, int nWaveNum, char * waveformFile);

// Dump waveform description to a file.
API hibStatus_t hibDumpWaveform(int nHibChainNum, int nWaveNum, char * waveformFile);

// Load waveform from a waveform knotArray.
API hibStatus_t hibSetWaveform(int nHibChainNum, int nWaveNum, hibWaveKnot_t *pWaveKnots);

// Get current waveform definition in form of a knotArray.
API hibStatus_t hibGetWaveform(int nHibChainNum, int nWaveNum, hibWaveKnot_t *pWaveKnots);

// Set the waveform to be used for binary mode printing.
API hibStatus_t hibSetActiveWaveform(int nHibChainNum, int nWaveNum);

// Set grayscale mode. 0 = binary. 1,2 = grayscale.
API hibStatus_t hibSetGrayscaleMode(int nHibChainNum, int nMode);

// Set waveform bias voltage. (not valid for M/T series heads).
API hibStatus_t hibSetWaveformBias(int nHibChainNum, float fBiasVoltage);

// Do waveform calibration.
API hibStatus_t hibDoWaveCal(int nHibChainNum, bool bResetCalData, bool bDoCal, float * fVppScale, float * fVssScale);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Autofire and Strobe Configuration Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
// Load 64-bit data pattern for jet autofiring. Two patterns. Can be used for main and background.
API hibStatus_t hibSetAutofirePattern(int nHibChainNum, unsigned nPatternLow, unsigned nPatternHigh, int nPatternNum);

// Accessors for list that defines autofire pattern for each jet ( 0 = mask, 1 = pattern1, 2 = pattern2).
API hibStatus_t hibGetAutofireMask(int nHibChainNum, int nNumVals, int *pAutofireMaskList);
API hibStatus_t hibLoadAutofireMask(int nHibChainNum, int nNumVals, int *pAutofireMaskList);
API hibStatus_t hibSetAutofireMask(int nHibChainNum, int nJet, int nMaskVal);

// Start/stop autofire
API hibStatus_t hibAutofireStart(int nHibChainNum, float fFireRateHz, unsigned nPatternOffLength, unsigned nPatternOnLength, unsigned nFireCount = 0);
API hibStatus_t hibAutofireStop(int nHibChainNum);
API hibStatus_t hibSetAutofireFreq(int nHibChainNum, float fFreqHz);
API hibStatus_t hibGetAutofireCount(int nHibChainNum, unsigned *pnFireCount);
// Configure camera and strobe.
API hibStatus_t hibSetCameraStrobeConfig(int nHibChainNum, hibCameraStrobe_t *pCameraStrobeConfig);
API hibStatus_t hibGetCameraStrobeConfig(int nHibChainNum, hibCameraStrobe_t *pCameraStrobeConfig);
API hibStatus_t hibSetStrobeFreeRun(int nHibChainNum, int nFreeRunState);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Image gather and print Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
#define MAX_COLORS 4

API hibStatus_t hibResetGather();
API hibStatus_t hibLoadImageFile(int nColorNum, char * filename, int nImageXResDpiOverride, int nMode);
API hibStatus_t hibLoadImageFileX(int nColorNum, char * filename, int nImageXResDpiOverride, int nImageYResDpiOverride, int nMode, int nXStart, int nYStart, int xtra1 = 0, int xtra2 = 0);
API hibStatus_t hibCreateImageBuffer(int nColorNum, int nWidth, int nHeight, int nXResDpi, int nYResDpi = 0);
API hibStatus_t hibLoadImage(int nColorNum, int nXStartOffset, int nYStartOffset, int nWidth, int nHeight, char * pImgData, int nMode);
API hibStatus_t hibFillImage(int nColorNum, int nXStartOffset, int nYStartOffset, int nWidth, int nHeight, unsigned char nValue, int nMode);

API hibStatus_t hibGatherImage(int nHibChainNum, int nColOffset, int nFirstHeadCol, int nLastHeadCol, int nRowOffset, int nYResDpi, bool reversePrint);
API hibStatus_t hibGetLastGatheredImage(int nHibChainNum, unsigned char **pGatheredImage, int * nByteCount);
API hibStatus_t hibClearGatheredImages(int nHibChainNum);
API hibStatus_t hibShowGatheredImages(int nHibChainNum);
API hibStatus_t hibSetImageSequence(int nHibChainNum, int * pImageSeq, int nSeqSize);
API hibStatus_t hibSetImageCount(int nHibChainNum, int * pImageCount, int nImageListSize);
API hibStatus_t hibSetSeqRepeatCount(int nHibChainNum, int nRepeatCount, int nRepeatSeqStartNum = 1);
API hibStatus_t hibSetSeqRepeatCountX(int nHibChainNum, int nRepeatCount, int nRepeatSeqStartNum = 1, int nRepeatSeqStopNum = 0, int xtra1 = 0, int xtra2 = 0);
API hibStatus_t hibStartPrintJob(int nHibChainNum);
API hibStatus_t hibStopPrintJob(int nHibChainNum);

// The following are for the new method of image processing. Images are applied to a printBar, rather than a head, and must be
// packed in column order, in 32 bit words, each word having data for 32 fire times (16 for grayscale mode), lsb is first fire
// time. The data for each image column must be word aligned, so the last word for each image column should be padded with 0's
// if the image length is not a multiple of 32 (16 for grayscale) pixels.
API hibStatus_t hibAddHeadToPrintBar(int nPrintBarNum, int nPrintBarHdNum, int nHibNum, int nFirstImgCol, int nFirstHdCol, int nLastHdCol);
API hibStatus_t hibConfigPrintBarHead(int nPrintBarNum, int nPrintBarHdNum, int nFirstImgCol, int nFirstHdCol, int nLastHdCol);
API hibStatus_t hibSetPrintBarRes(int nPrintBarNum, float fPbResDpi);
API hibStatus_t hibShowPrintBar(int nPrintBarNum);
API hibStatus_t hibPackImage(int nPrintBarNum, int nYResDpi, bool bReversePrint);
API hibStatus_t hibPackImageToFile(int nPrintBarNum, char * piFilename, int nYResDpi, bool bReversePrint);
API hibStatus_t hibPackBmpToFile(char * bmpFilename[], int nNumColors, char * piFilename, int nPrintResDpi, int nBitsPerPixel, bool bReversePrint, int nBmpXResOverride, int nBmpYResOverride, int nXStart, int nYStart, int nXSize, int nYSize);
API hibStatus_t hibGetLastPackedImage(int nPrintBarNum, packedCbImg_t * pPackedImage);
API hibStatus_t hibClearPackedImages(int nPrintBarNum);
API hibStatus_t hibShowPackedImages(int nPrintBarNum);

API hibStatus_t hibConfigNonFire(int nHibChainNum, bool bEnableNonFire, int nMinPixelCount, int nMaxPixelCount, int nMinNonFireCount, int nMaxNonFireCount);
API hibStatus_t hibGetNonFireLength(int nHibChainNum, int * pnNonFireLengthPixels);
API hibStatus_t hibSetImageGap(int nHibChainNum, int nImageGapPixels);
API hibStatus_t hibSetImageStartOffset(int nHibChainNum, int nImageStartOffsetPixels);
API hibStatus_t hibSetMarginCrop(int nHibChainNum, int nLeadMarginCropPixels, int nTrailMarginCropPixels);
API hibStatus_t hibSetImageCrop(int nHibChainNum, int nLeadImagePixel, int nTrailImagePixel);
API hibStatus_t hibSetWidthCrop(int nHibChainNum, int nLeftImagePixel, int nRightImagePixel);
API hibStatus_t hibConfigHmjHiding(int nHibChainNum, bool bHideHmj);

API hibStatus_t hibConfigPrintJob(int nPrintBarNum, int nNumPasses, bool *pbPassRevPrint, int *pnPassImgColOffset, int *pnPassHeadColOffset, int *pnPassXtra1, int *pnPassXtra2, float fHeadPrintRes, float fImagingRes);

API hibStatus_t hibSetPackedImageSequence(int nPrintBarNum, int * pImageSeq, int nSeqSize);
API hibStatus_t hibSetPackedImageCount(int nPrintBarNum, int * pImageCount, int nImageListSize);
API hibStatus_t hibSetPackedSeqRepeatCount(int nPrintBarNum, int nRepeatCount, int nRepeatSeqStartNum, int nRepeatSeqStopNum, int xtra1, int xtra2);

//////////////////////////////////////////////////////////////////////////////////////////
//
//				Hardware Interrupt Notification Functions
// 
//////////////////////////////////////////////////////////////////////////////////////////
typedef void(*interruptCallback_t)(int nHibChainNum, unsigned int irqMask, void *pUserData);
API hibStatus_t hibSetIrqHandler(int boardNum, interruptCallback_t irqCallback, unsigned int irqMaskR, unsigned int irqMaskF, void *pUserData);


// Enumerate the various interrupts from the FPGA that the app may register
// for notification using hibSetIrqHandler()
typedef enum _hibInterruptFlags_t
{
	hibHeadDmaErrorIrq =	(1 << 25),
	hibHeadDmaUnderrunIrq = (1 << 24),
	hibFifoPageTimeoutIrq = (1 << 22),
	hibWaveAmpOverTempIrq = (1 << 18),
	hibWaveGenFaultIrq =	(1 << 17),
	hibWaveAmpFaultIrq =	(1 << 16),
	hibHeadSerialReadyIrq = (1 << 13),
	hibHeaterBoardFaultIrq = (1 << 8),
	hibDotPllErrorIrq =		(1 << 6),
	hibPageActiveIrq =		(1 << 4),
	hibSequenceDotClock =	(1 << 1),
	hibSequencePageStart =	(1 << 0)
};

API hibStatus_t hibWaitForPageActive(int nHibChainNum, int nPageActiveState, int nTimeoutMs);
API hibStatus_t hibWaitForDmaUnderRun(int nHibChainNum, int nDmaUnderRunState, int nTimeoutMs);

// Hib and head register direct access
API hibStatus_t hibReadHib(int nHibChainNum, int nHibRamOffset, int *pHibRamVals, int nNumValues);
API hibStatus_t hibReadHead(int nHibChainNum, int nHeadRamOffset, unsigned *pHeadRamVals, int nNumValues);
API hibStatus_t hibReadHead16(int nHibChainNum, int nHeadRamOffset, unsigned *pHeadRamVals, int nNumValues);


//
//	Type definitions and function prototypes related to checking the DC voltage supplies
//

// Typedef to create an enum for each nominal voltage.  Use the in requesting regulated voltage checks
typedef enum _hibDCvoltages_t
{
	// nominal DC voltage
	hibPos12Volt,		// +12	volt
	hibNeg12Volt,		// -12  volt
	hibPos5Volt,		//  +5	volt
	hibPos1_2Volt,		//  +1.2 volt
	hibPos15Volt,		// +15  volt
	hibNeg15Volt,		// -15	volt
	hibNegWaveVolt,		// waveamp negative supply
	hibPosWaveVolt,		// waveamp positive supply
	hibHeaterVolt,		// heater supply
	hibHeaterLmtVolt	// heater current limited supply
} hibDCvoltages_t;

// Function used to ask for the actual voltage for any of the regulated DC supplies on the HIB.
API hibStatus_t hibReadVoltageValue(int nHibChainNum, hibDCvoltages_t voltageSelector, float *pActualV);


// Enumerate the various bit masks for the power supply checks.  These bit assignments
// match those used in the HIB FPGA registers.
typedef enum _hibPowerSupplyOkFlags_t
{
	hibHeaterMask =		(1 << 16),
	hibPos12VoltMask =	(1 << 15),
	hibPos15VoltMask =	(1 << 14),
	hibPosWaveampMask =	(1 << 13),
	hibNegWaveampMask =	(1 << 12),
	hibPos5VoltMask =	(1 << 11),
	hibNeg15VoltMask =	(1 << 10),
	hibNeg12VoltMask =	(1 << 9),
	hibPos1_2VoltMask =	(1 << 8)
} hibPowerSupplyFlags_t;

// Function to check to see if all regulated supplies are within tolerance.  The callers
// pSupplyErrorFlags variable will be set indicate all errors using the bit values above.
API hibStatus_t hibCheckRegulatedVoltages(int nHibChainNum, unsigned *pSupplyErrorFlags);


//////////////////////////////////////////////////////////////////////////////////////////
//		
//			Other Items (yet to be categorized)
// 
//			Are these "Head Geometry" items?
//			Are these used as part of the API entry functions?
//
//////////////////////////////////////////////////////////////////////////////////////////
// Flash a fpga binary image into the HIB's SPI flash memory
API hibStatus_t	hibFlashFpgaFromFile(int nHibChainNum, char *fpgaBinaryFile);
// Verify Fpga binary image: compare it with the contents of a file
API hibStatus_t	hibVerifyFpgaFromFile(int nHibChainNum, char *fpgaBinaryFile);

API hibStatus_t	hibFlashHeadFpgaFromFile(int nHibChainNum, char *fpgaBinaryFile, bool goldenCopy = false);
API hibStatus_t	hibVerifyHeadFpgaFromFile(int nHibChainNum, char *fpgaBinaryFile, bool goldenCopy = false);

API hibStatus_t hibGetJetDropSizes(int nHibChainNum, int nNumJets, int *pJetDropSizes);
API hibStatus_t hibSetJetDropSizes(int nHibChainNum, int nNumJets, int *pJetDropSizes);
API hibStatus_t hibSetUpperArrayDropSize(int nHibChainNum, int nDropSize);
API hibStatus_t hibSetLowerArrayDropSize(int nHibChainNum, int nDropSize);



#ifdef __cplusplus
}
#endif


#endif // HIB_LIB_API_H  End of header guard