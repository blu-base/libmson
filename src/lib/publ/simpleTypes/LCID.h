#ifndef LCID_H
#define LCID_H

#include <QtCore/qglobal.h>

#include <QDataStream>

#include "../../priv/IStreamable.h"

namespace libmson {

/** @brief presribed settable languages
 *
 *  according to [MS-ONE] section 2.3.26
 */
enum class LanguageID : quint16 {
  ar             = 0x0001,
  bg             = 0x0002,
  ca             = 0x0003,
  zh_Hans        = 0x0004,
  cs             = 0x0005,
  da             = 0x0006,
  de             = 0x0007,
  el             = 0x0008,
  en             = 0x0009,
  es             = 0x000A,
  fi             = 0x000B,
  fr             = 0x000C,
  he             = 0x000D,
  hu             = 0x000E,
  is             = 0x000F,
  it             = 0x0010,
  ja             = 0x0011,
  ko             = 0x0012,
  nl             = 0x0013,
  no             = 0x0014,
  pl             = 0x0015,
  pt             = 0x0016,
  rm             = 0x0017,
  ro             = 0x0018,
  ru             = 0x0019,
  hr             = 0x001A,
  sk             = 0x001B,
  sq             = 0x001C,
  sv             = 0x001D,
  th             = 0x001E,
  tr             = 0x001F,
  ur             = 0x0020,
  id             = 0x0021,
  uk             = 0x0022,
  be             = 0x0023,
  sl             = 0x0024,
  et             = 0x0025,
  lv             = 0x0026,
  lt             = 0x0027,
  tg             = 0x0028,
  fa             = 0x0029,
  vi             = 0x002A,
  hy             = 0x002B,
  az             = 0x002C,
  eu             = 0x002D,
  hsb            = 0x002E,
  mk             = 0x002F,
  st             = 0x0030,
  ts             = 0x0031,
  tn             = 0x0032,
  ve             = 0x0033,
  xh             = 0x0034,
  zu             = 0x0035,
  af             = 0x0036,
  ka             = 0x0037,
  fo             = 0x0038,
  hi             = 0x0039,
  mt             = 0x003A,
  se             = 0x003B,
  ga             = 0x003C,
  yi             = 0x003D,
  ms             = 0x003E,
  kk             = 0x003F,
  ky             = 0x0040,
  sw             = 0x0041,
  tk             = 0x0042,
  uz             = 0x0043,
  tt             = 0x0044,
  bn             = 0x0045,
  pa             = 0x0046,
  gu             = 0x0047,
  l_or           = 0x0048,
  ta             = 0x0049,
  te             = 0x004A,
  kn             = 0x004B,
  ml             = 0x004C,
  as             = 0x004D,
  mr             = 0x004E,
  sa             = 0x004F,
  mn             = 0x0050,
  bo             = 0x0051,
  cy             = 0x0052,
  km             = 0x0053,
  lo             = 0x0054,
  my             = 0x0055,
  gl             = 0x0056,
  kok            = 0x0057,
  mni            = 0x0058,
  sd             = 0x0059,
  syr            = 0x005A,
  si             = 0x005B,
  chr            = 0x005C,
  iu             = 0x005D,
  am             = 0x005E,
  tzm            = 0x005F,
  ks             = 0x0060,
  ne             = 0x0061,
  fy             = 0x0062,
  ps             = 0x0063,
  fil            = 0x0064,
  dv             = 0x0065,
  bin            = 0x0066,
  ff             = 0x0067,
  ha             = 0x0068,
  ibb            = 0x0069,
  yo             = 0x006A,
  quz            = 0x006B,
  nso            = 0x006C,
  ba             = 0x006D,
  lb             = 0x006E,
  kl             = 0x006F,
  ig             = 0x0070,
  kr             = 0x0071,
  om             = 0x0072,
  ti             = 0x0073,
  gn             = 0x0074,
  haw            = 0x0075,
  la             = 0x0076,
  so             = 0x0077,
  ii             = 0x0078,
  pap            = 0x0079,
  arn            = 0x007A,
  moh            = 0x007C,
  br             = 0x007E,
  invariant      = 0x007F,
  ug             = 0x0080,
  mi             = 0x0081,
  oc             = 0x0082,
  co             = 0x0083,
  gsw            = 0x0084,
  sah            = 0x0085,
  qut            = 0x0086,
  rw             = 0x0087,
  wo             = 0x0088,
  prs            = 0x008C,
  gd             = 0x0091,
  ku             = 0x0092,
  quc            = 0x0093,
  ar_SA          = 0x0401,
  bg_BG          = 0x0402,
  ca_ES          = 0x0403,
  zh_TW          = 0x0404,
  cs_CZ          = 0x0405,
  da_DK          = 0x0406,
  de_DE          = 0x0407,
  el_GR          = 0x0408,
  en_US          = 0x0409,
  es_ES_tradnl   = 0x040A,
  fi_FI          = 0x040B,
  fr_FR          = 0x040C,
  he_IL          = 0x040D,
  hu_HU          = 0x040E,
  is_IS          = 0x040F,
  it_IT          = 0x0410,
  ja_JP          = 0x0411,
  ko_KR          = 0x0412,
  nl_NL          = 0x0413,
  nb_NO          = 0x0414,
  pl_PL          = 0x0415,
  pt_BR          = 0x0416,
  rm_CH          = 0x0417,
  ro_RO          = 0x0418,
  ru_RU          = 0x0419,
  hr_HR          = 0x041A,
  sk_SK          = 0x041B,
  sq_AL          = 0x041C,
  sv_SE          = 0x041D,
  th_TH          = 0x041E,
  tr_TR          = 0x041F,
  ur_PK          = 0x0420,
  id_ID          = 0x0421,
  uk_UA          = 0x0422,
  be_BY          = 0x0423,
  sl_SI          = 0x0424,
  et_EE          = 0x0425,
  lv_LV          = 0x0426,
  lt_LT          = 0x0427,
  tg_Cyrl_TJ     = 0x0428,
  fa_IR          = 0x0429,
  vi_VN          = 0x042A,
  hy_AM          = 0x042B,
  az_Latn_AZ     = 0x042C,
  eu_ES          = 0x042D,
  hsb_DE         = 0x042E,
  mk_MK          = 0x042F,
  st_ZA          = 0x0430,
  ts_ZA          = 0x0431,
  tn_ZA          = 0x0432,
  ve_ZA          = 0x0433,
  xh_ZA          = 0x0434,
  zu_ZA          = 0x0435,
  af_ZA          = 0x0436,
  ka_GE          = 0x0437,
  fo_FO          = 0x0438,
  hi_IN          = 0x0439,
  mt_MT          = 0x043A,
  se_NO          = 0x043B,
  yi_Hebr        = 0x043D,
  ms_MY          = 0x043E,
  kk_KZ          = 0x043F,
  ky_KG          = 0x0440,
  sw_KE          = 0x0441,
  tk_TM          = 0x0442,
  uz_Latn_UZ     = 0x0443,
  tt_RU          = 0x0444,
  bn_IN          = 0x0445,
  pa_IN          = 0x0446,
  gu_IN          = 0x0447,
  or_IN          = 0x0448,
  ta_IN          = 0x0449,
  te_IN          = 0x044A,
  kn_IN          = 0x044B,
  ml_IN          = 0x044C,
  as_IN          = 0x044D,
  mr_IN          = 0x044E,
  sa_IN          = 0x044F,
  mn_MN          = 0x0450,
  bo_CN          = 0x0451,
  cy_GB          = 0x0452,
  km_KH          = 0x0453,
  lo_LA          = 0x0454,
  my_MM          = 0x0455,
  gl_ES          = 0x0456,
  kok_IN         = 0x0457,
  mni_IN         = 0x0458,
  sd_Deva_IN     = 0x0459,
  syr_SY         = 0x045A,
  si_LK          = 0x045B,
  chr_Cher_US    = 0x045C,
  iu_Cans_CA     = 0x045D,
  am_ET          = 0x045E,
  tzm_Arab_MA    = 0x045F,
  ks_Arab        = 0x0460,
  ne_NP          = 0x0461,
  fy_NL          = 0x0462,
  ps_AF          = 0x0463,
  fil_PH         = 0x0464,
  dv_MV          = 0x0465,
  bin_NG         = 0x0466,
  fuv_NG         = 0x0467,
  ha_Latn_NG     = 0x0468,
  ibb_NG         = 0x0469,
  yo_NG          = 0x046A,
  quz_BO         = 0x046B,
  nso_ZA         = 0x046C,
  ba_RU          = 0x046D,
  lb_LU          = 0x046E,
  kl_GL          = 0x046F,
  ig_NG          = 0x0470,
  kr_NG          = 0x0471,
  om_ET          = 0x0472,
  ti_ET          = 0x0473,
  gn_PY          = 0x0474,
  haw_US         = 0x0475,
  la_Latn        = 0x0476,
  so_SO          = 0x0477,
  ii_CN          = 0x0478,
  pap_029        = 0x0479,
  arn_CL         = 0x047A,
  moh_CA         = 0x047C,
  br_FR          = 0x047E,
  ug_CN          = 0x0480,
  mi_NZ          = 0x0481,
  oc_FR          = 0x0482,
  co_FR          = 0x0483,
  gsw_FR         = 0x0484,
  sah_RU         = 0x0485,
  qut_GT         = 0x0486,
  rw_RW          = 0x0487,
  wo_SN          = 0x0488,
  prs_AF         = 0x048C,
  plt_MG         = 0x048D,
  zh_yue_HK      = 0x048E,
  tdd_Tale_CN    = 0x048F,
  khb_Talu_CN    = 0x0490,
  gd_GB          = 0x0491,
  ku_Arab_IQ     = 0x0492,
  quc_CO         = 0x0493,
  qps_ploc       = 0x0501,
  qps_ploca      = 0x05FE,
  ar_IQ          = 0x0801,
  ca_ES_valencia = 0x0803,
  zh_CN          = 0x0804,
  de_CH          = 0x0807,
  en_GB          = 0x0809,
  es_MX          = 0x080A,
  fr_BE          = 0x080C,
  it_CH          = 0x0810,
  ja_Ploc_JP     = 0x0811,
  nl_BE          = 0x0813,
  nn_NO          = 0x0814,
  pt_PT          = 0x0816,
  ro_MD          = 0x0818,
  ru_MD          = 0x0819,
  sr_Latn_CS     = 0x081A,
  sv_FI          = 0x081D,
  ur_IN          = 0x0820,
  az_Cyrl_AZ     = 0x082C,
  dsb_DE         = 0x082E,
  tn_BW          = 0x0832,
  se_SE          = 0x083B,
  ga_IE          = 0x083C,
  ms_BN          = 0x083E,
  kk_Latn_KZ     = 0x083F,
  uz_Cyrl_UZ     = 0x0843,
  bn_BD          = 0x0845,
  pa_Arab_PK     = 0x0846,
  ta_LK          = 0x0849,
  mn_Mong_CN     = 0x0850,
  bo_BT          = 0x0851,
  sd_Arab_PK     = 0x0859,
  iu_Latn_CA     = 0x085D,
  tzm_Latn_DZ    = 0x085F,
  ks_Deva        = 0x0860,
  ne_IN          = 0x0861,
  ff_Latn_SN     = 0x0867,
  quz_EC         = 0x086B,
  ti_ER          = 0x0873,
  qps_plocm      = 0x09FF,
  ar_EG          = 0x0C01,
  zh_HK          = 0x0C04,
  de_AT          = 0x0C07,
  en_AU          = 0x0C09,
  es_ES          = 0x0C0A,
  fr_CA          = 0x0C0C,
  sr_Cyrl_CS     = 0x0C1A,
  se_FI          = 0x0C3B,
  mn_Mong_MN     = 0x0C50,
  dz_BT          = 0x0C51,
  tmz_MA         = 0x0C5F,
  quz_PE         = 0x0C6b,
  ar_LY          = 0x1001,
  zh_SG          = 0x1004,
  de_LU          = 0x1007,
  en_CA          = 0x1009,
  es_GT          = 0x100A,
  fr_CH          = 0x100C,
  hr_BA          = 0x101A,
  smj_NO         = 0x103B,
  tzm_Tfng_MA    = 0x105F,
  ar_DZ          = 0x1401,
  zh_MO          = 0x1404,
  de_LI          = 0x1407,
  en_NZ          = 0x1409,
  es_CR          = 0x140A,
  fr_LU          = 0x140C,
  bs_Latn_BA     = 0x141A,
  smj_SE         = 0x143B,
  ar_MA          = 0x1801,
  en_IE          = 0x1809,
  es_PA          = 0x180A,
  fr_MC          = 0x180C,
  sr_Latn_BA     = 0x181A,
  sma_NO         = 0x183B,
  ar_TN          = 0x1C01,
  en_ZA          = 0x1C09,
  es_DO          = 0x1C0A,
  sr_Cyrl_BA     = 0x1C1A,
  sma_SE         = 0x1C3B,
  ar_OM          = 0x2001,
  en_JM          = 0x2009,
  es_VE          = 0x200A,
  fr_RE          = 0x200C,
  bs_Cyrl_BA     = 0x201A,
  sms_FI         = 0x203B,
  ar_YE          = 0x2401,
  en_029         = 0x2409,
  es_CO          = 0x240A,
  fr_CD          = 0x240C,
  sr_Latn_RS     = 0x241A,
  smn_FI         = 0x243B,
  ar_SY          = 0x2801,
  en_BZ          = 0x2809,
  es_PE          = 0x280A,
  fr_SN          = 0x280C,
  sr_Cyrl_RS     = 0x281A,
  ar_JO          = 0x2C01,
  en_TT          = 0x2C09,
  es_AR          = 0x2C0A,
  fr_CM          = 0x2C0C,
  sr_Latn_ME     = 0x2C1A,
  ar_LB          = 0x3001,
  en_ZW          = 0x3009,
  es_EC          = 0x300A,
  fr_CI          = 0x300C,
  sr_Cyrl_ME     = 0x301A,
  ar_KW          = 0x3401,
  en_PH          = 0x3409,
  es_CL          = 0x340A,
  fr_ML          = 0x340C,
  ar_AE          = 0x3801,
  en_ID          = 0x3809,
  es_UY          = 0x380A,
  fr_MA          = 0x380C,
  ar_BH          = 0x3c01,
  en_HK          = 0x3c09,
  es_PY          = 0x3c0A,
  fr_HT          = 0x3c0C,
  ar_QA          = 0x4001,
  en_IN          = 0x4009,
  es_BO          = 0x400A,
  ar_Ploc_SA     = 0x4401,
  en_MY          = 0x4409,
  es_SV          = 0x440A,
  ar_145         = 0x4801,
  en_SG          = 0x4809,
  es_HN          = 0x480A,
  en_AE          = 0x4C09,
  es_NI          = 0x4C0A,
  en_BH          = 0x5009,
  es_PR          = 0x500A,
  en_EG          = 0x5409,
  es_US          = 0x540A,
  en_JO          = 0x5809,
  es_419         = 0x580A,
  en_KW          = 0x5C09,
  es_CU          = 0x5C0A,
  en_TR          = 0x6009,
  en_YE          = 0x6409,
  bs_Cyrl        = 0x641A,
  bs_Latn        = 0x681A,
  sr_Cyrl        = 0x6C1A,
  sr_Latn        = 0x701A,
  smn            = 0x703B,
  az_Cyrl        = 0x742C,
  sms            = 0x743B,
  zh             = 0x7804,
  nn             = 0x7814,
  bs             = 0x781A,
  az_Latn        = 0x782C,
  sma            = 0x783B,
  kk_Cyrl        = 0x783F,
  uz_Cyrl        = 0x7843,
  mn_Cyrl        = 0x7850,
  iu_Cans        = 0x785D,
  tzm_Tfng       = 0x785F,
  zh_Hant        = 0x7C04,
  nb             = 0x7C14,
  sr             = 0x7C1A,
  tg_Cyrl        = 0x7C28,
  dsb            = 0x7C2E,
  smj            = 0x7C3B,
  kk_Latn        = 0x7C3F,
  uz_Latn        = 0x7C43,
  pa_Arab        = 0x7C46,
  mn_Mong        = 0x7C50,
  sd_Arab        = 0x7C59,
  chr_Cher       = 0x7C5C,
  iu_Latn        = 0x7C5D,
  tzm_Latn       = 0x7C5F,
  ff_Latn        = 0x7C67,
  ha_Latn        = 0x7C68,
  ku_Arab        = 0x7C92,
  reservedF2EE   = 0xF2EE,
  fr_015         = 0xE40C,
  reservedEEEE   = 0xEEEE,
  invalid        = 0xFFFF
};

/// \todo refactor LCID class. sortid, and toString are not well designed
/** @class LCID
 *  @brief specifies the language in the node referencing this class
 *
 *  represents the simple type according to [MS-ONE] section 2.3.26, and
 * [MS-LCID]
 *
 */
class LCID : public priv::IStreamable {
  LanguageID lid;
  quint8 sortid;

public:
  LCID();

  QString languageIDtoString() const;
  static QString languageIDtoString(const LanguageID& l_id);

  void setLCID(const LanguageID& lid);
  LanguageID getLCID() const;

  void setSortID(const quint8 sid);
  quint8 getSortID() const;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace libmson

#endif // LCID_H
