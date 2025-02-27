/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef META_DATA_H_

#define META_DATA_H_

#include <sys/types.h>

#include <stdint.h>

#include <utils/RefBase.h>
#include <utils/KeyedVector.h>
#include <utils/String8.h>

namespace android {

// The following keys map to int32_t data unless indicated otherwise.
enum {
    kKeyMIMEType          = 'mime',  // cstring
    kKeyWidth             = 'widt',  // int32_t, image pixel
    kKeyHeight            = 'heig',  // int32_t, image pixel
    kKeyDisplayWidth      = 'dWid',  // int32_t, display/presentation
    kKeyDisplayHeight     = 'dHgt',  // int32_t, display/presentation
    kKeySARWidth          = 'sarW',  // int32_t, sampleAspectRatio width
    kKeySARHeight         = 'sarH',  // int32_t, sampleAspectRatio height

    // a rectangle, if absent assumed to be (0, 0, width - 1, height - 1)
    kKeyCropRect          = 'crop',

    kKeyRotation          = 'rotA',  // int32_t (angle in degrees)
    kKeyIFramesInterval   = 'ifiv',  // int32_t
    kKeyStride            = 'strd',  // int32_t
    kKeySliceHeight       = 'slht',  // int32_t
    kKeyChannelCount      = '#chn',  // int32_t
    kKeyChannelMask       = 'chnm',  // int32_t
    kKeySampleRate        = 'srte',  // int32_t (audio sampling rate Hz)
    kkBitsPerSample       = 'btsp', //int32_t (bits per sample)
    kKeyFrameRate         = 'frmR',  // int32_t (video frame rate fps)
#ifdef CONFIG_SPRD_RECORD_EIS
    kKeyEISMode           ='eis',
    kKeyActualTime        ='actu',
#endif
    kKeyBitRate           = 'brte',  // int32_t (bps)
    kKeyBlockAlign        = 'blka',  // int32_t
    kKeyESDS              = 'esds',  // raw data
    kKeyAACProfile        = 'aacp',  // int32_t
    kKeyAVCC              = 'avcc',  // raw data
    kKeyHVCC              = 'hvcc',  // raw data
    kKeyD263              = 'd263',  // raw data
    kKeyVorbisInfo        = 'vinf',  // raw data
    kKeyVorbisBooks       = 'vboo',  // raw data
    kKeyOpusHeader        = 'ohdr',  // raw data
    kKeyOpusCodecDelay    = 'ocod',  // uint64_t (codec delay in ns)
    kKeyOpusSeekPreRoll   = 'ospr',  // uint64_t (seek preroll in ns)
    kKeyWantsNALFragments = 'NALf',
    kKeyIsSyncFrame       = 'sync',  // int32_t (bool)
    kKeyIsCodecConfig     = 'conf',  // int32_t (bool)
    kKeyTime              = 'time',  // int64_t (usecs)
    kKeyDecodingTime      = 'decT',  // int64_t (decoding timestamp in usecs)
    kKeyNTPTime           = 'ntpT',  // uint64_t (ntp-timestamp)
    kKeyTargetTime        = 'tarT',  // int64_t (usecs)
    kKeyDriftTime         = 'dftT',  // int64_t (usecs)
    kKeyAnchorTime        = 'ancT',  // int64_t (usecs)
    kKeyDuration          = 'dura',  // int64_t (usecs)
    kKeyPixelFormat       = 'pixf',  // int32_t
    kKeyColorFormat       = 'colf',  // int32_t
    kKeyColorSpace        = 'cols',  // int32_t
    kKeyPlatformPrivate   = 'priv',  // pointer
    kKeyDecoderComponent  = 'decC',  // cstring
    kKeyBufferID          = 'bfID',
    kKeyMaxInputSize      = 'inpS',
    kKeyMaxWidth          = 'maxW',
    kKeyMaxHeight         = 'maxH',
    kKeyThumbnailTime     = 'thbT',  // int64_t (usecs)
    kKeyTrackID           = 'trID',
    kKeyIsDRM             = 'idrm',  // int32_t (bool)
    kKeyEncoderDelay      = 'encd',  // int32_t (frames)
    kKeyEncoderPadding    = 'encp',  // int32_t (frames)

    kKeyAlbum             = 'albu',  // cstring
    kKeyArtist            = 'arti',  // cstring
    kKeyAlbumArtist       = 'aart',  // cstring
    kKeyComposer          = 'comp',  // cstring
    kKeyGenre             = 'genr',  // cstring
    kKeyTitle             = 'titl',  // cstring
    kKeyYear              = 'year',  // cstring
    kKeyAlbumArt          = 'albA',  // compressed image data
    kKeyAlbumArtMIME      = 'alAM',  // cstring
    kKeyAuthor            = 'auth',  // cstring
    kKeyCDTrackNumber     = 'cdtr',  // cstring
    kKeyDiscNumber        = 'dnum',  // cstring
    kKeyDate              = 'date',  // cstring
    kKeyWriter            = 'writ',  // cstring
    kKeyCompilation       = 'cpil',  // cstring
    kKeyLocation          = 'loc ',  // cstring
    kKeyTimeScale         = 'tmsl',  // int32_t
    kKeyCaptureFramerate  = 'capF',  // float (capture fps)

    // video profile and level
    kKeyVideoProfile      = 'vprf',  // int32_t
    kKeyVideoLevel        = 'vlev',  // int32_t

    // Set this key to enable authoring files in 64-bit offset
    kKey64BitFileOffset   = 'fobt',  // int32_t (bool)
    kKey2ByteNalLength    = '2NAL',  // int32_t (bool)

    // Identify the file output format for authoring
    // Please see <media/mediarecorder.h> for the supported
    // file output formats.
    kKeyFileType          = 'ftyp',  // int32_t

    // Track authoring progress status
    // kKeyTrackTimeStatus is used to track progress in elapsed time
    kKeyTrackTimeStatus   = 'tktm',  // int64_t

    kKeyRealTimeRecording = 'rtrc',  // bool (int32_t)
    kKeyNumBuffers        = 'nbbf',  // int32_t

    // Ogg files can be tagged to be automatically looping...
    kKeyAutoLoop          = 'autL',  // bool (int32_t)

    kKeyValidSamples      = 'valD',  // int32_t

    kKeyIsUnreadable      = 'unre',  // bool (int32_t)

    // An indication that a video buffer has been rendered.
    kKeyRendered          = 'rend',  // bool (int32_t)

    // The language code for this media
    kKeyMediaLanguage     = 'lang',  // cstring

    // To store the timed text format data
    kKeyTextFormatData    = 'text',  // raw data

    kKeyRequiresSecureBuffers = 'secu',  // bool (int32_t)

    kKeyIsADTS            = 'adts',  // bool (int32_t)
    kKeyAACAOT            = 'aaot',  // int32_t

    // If a MediaBuffer's data represents (at least partially) encrypted
    // data, the following fields aid in decryption.
    // The data can be thought of as pairs of plain and encrypted data
    // fragments, i.e. plain and encrypted data alternate.
    // The first fragment is by convention plain data (if that's not the
    // case, simply specify plain fragment size of 0).
    // kKeyEncryptedSizes and kKeyPlainSizes each map to an array of
    // size_t values. The sum total of all size_t values of both arrays
    // must equal the amount of data (i.e. MediaBuffer's range_length()).
    // If both arrays are present, they must be of the same size.
    // If only encrypted sizes are present it is assumed that all
    // plain sizes are 0, i.e. all fragments are encrypted.
    // To programmatically set these array, use the MetaData::setData API, i.e.
    // const size_t encSizes[];
    // meta->setData(
    //  kKeyEncryptedSizes, 0 /* type */, encSizes, sizeof(encSizes));
    // A plain sizes array by itself makes no sense.
    kKeyEncryptedSizes    = 'encr',  // size_t[]
    kKeyPlainSizes        = 'plai',  // size_t[]
    kKeyCryptoKey         = 'cryK',  // uint8_t[16]
    kKeyCryptoIV          = 'cryI',  // uint8_t[16]
    kKeyCryptoMode        = 'cryM',  // int32_t

    kKeyCryptoDefaultIVSize = 'cryS',  // int32_t

    kKeyPssh              = 'pssh',  // raw data

    // Please see MediaFormat.KEY_IS_AUTOSELECT.
    kKeyTrackIsAutoselect = 'auto', // bool (int32_t)
    // Please see MediaFormat.KEY_IS_DEFAULT.
    kKeyTrackIsDefault    = 'dflt', // bool (int32_t)
    // Similar to MediaFormat.KEY_IS_FORCED_SUBTITLE but pertains to av tracks as well.
    kKeyTrackIsForced     = 'frcd', // bool (int32_t)

    // H264 supplemental enhancement information offsets/sizes
    kKeySEI               = 'sei ', // raw data
};

enum {
    kTypeESDS        = 'esds',
    kTypeAVCC        = 'avcc',
    kTypeHVCC        = 'hvcc',
    kTypeD263        = 'd263',
};

class MetaData : public RefBase {
public:
    MetaData();
    MetaData(const MetaData &from);

    enum Type {
        TYPE_NONE     = 'none',
        TYPE_C_STRING = 'cstr',
        TYPE_INT32    = 'in32',
        TYPE_INT64    = 'in64',
        TYPE_FLOAT    = 'floa',
        TYPE_POINTER  = 'ptr ',
        TYPE_RECT     = 'rect',
    };

    void clear();
    bool remove(uint32_t key);

    bool setCString(uint32_t key, const char *value);
    bool setInt32(uint32_t key, int32_t value);
    bool setInt64(uint32_t key, int64_t value);
    bool setFloat(uint32_t key, float value);
    bool setPointer(uint32_t key, void *value);

    bool setRect(
            uint32_t key,
            int32_t left, int32_t top,
            int32_t right, int32_t bottom);

    bool findCString(uint32_t key, const char **value);
    bool findInt32(uint32_t key, int32_t *value);
    bool findInt64(uint32_t key, int64_t *value);
    bool findFloat(uint32_t key, float *value);
    bool findPointer(uint32_t key, void **value);

    bool findRect(
            uint32_t key,
            int32_t *left, int32_t *top,
            int32_t *right, int32_t *bottom);

    bool setData(uint32_t key, uint32_t type, const void *data, size_t size);

    bool findData(uint32_t key, uint32_t *type,
                  const void **data, size_t *size) const;

    bool hasData(uint32_t key) const;

    void dumpToLog() const;

protected:
    virtual ~MetaData();

private:
    struct typed_data {
        typed_data();
        ~typed_data();

        typed_data(const MetaData::typed_data &);
        typed_data &operator=(const MetaData::typed_data &);

        void clear();
        void setData(uint32_t type, const void *data, size_t size);
        void getData(uint32_t *type, const void **data, size_t *size) const;
        String8 asString() const;

    private:
        uint32_t mType;
        size_t mSize;

        union {
            void *ext_data;
            float reservoir;
        } u;

        bool usesReservoir() const {
            return mSize <= sizeof(u.reservoir);
        }

        void *allocateStorage(size_t size);
        void freeStorage();

        void *storage() {
            return usesReservoir() ? &u.reservoir : u.ext_data;
        }

        const void *storage() const {
            return usesReservoir() ? &u.reservoir : u.ext_data;
        }
    };

    struct Rect {
        int32_t mLeft, mTop, mRight, mBottom;
    };

    KeyedVector<uint32_t, typed_data> mItems;

    // MetaData &operator=(const MetaData &);
};

}  // namespace android

#endif  // META_DATA_H_
