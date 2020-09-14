#include "LCID.h"

#include "../helper/Helper.h"

namespace MSONcommon {

LCID::LCID() : lid(LanguageID::invalid), sortid() {}

QString LCID::toString() const
{
  return LCID::toString(lid);
}



void LCID::setLCID(const LanguageID lid)
{
  this->lid = lid;
}

LanguageID LCID::getLCID() const
{
  return lid;
}




void LCID::setSortID(const quint8 sid)
{
  sortid = sid;
}

quint8 LCID::getSortID() const
{
  return sortid;
}

void LCID::deserialize(QDataStream &ds) {
  quint16 lvalue;
  ds >> lvalue;
  quint16 svalue;
  ds >> svalue;


  lid = static_cast<LanguageID>(lvalue);
  sortid = svalue & 0xF;
}

void LCID::serialize(QDataStream &ds) const {

  quint32 value = static_cast<quint32>(lid) << 16;
  value += sortid << 12;

  ds << value;
}

void LCID::writeLowLevelXml(QXmlStreamWriter& xmlWriter) const
{
  xmlWriter.writeStartElement("LCID");
  xmlWriter.writeAttribute("SortID", qStringHex(sortid,4));
  xmlWriter.writeCharacters(toString());
  xmlWriter.writeEndElement();
}

void LCID::toDebugString(QDebug &dbg) const { dbg << "LCID:\n"; }

QString LCID::toString(const LanguageID l_id) {
  switch (l_id) {
  case LanguageID::ar:
    return "ar";
  case LanguageID::bg:
    return "bg";
  case LanguageID::ca:
    return "ca";
  case LanguageID::zh_Hans:
    return "zh-Hans";
  case LanguageID::cs:
    return "cs";
  case LanguageID::da:
    return "da";
  case LanguageID::de:
    return "de";
  case LanguageID::el:
    return "el";
  case LanguageID::en:
    return "en";
  case LanguageID::es:
    return "es";
  case LanguageID::fi:
    return "fi";
  case LanguageID::fr:
    return "fr";
  case LanguageID::he:
    return "he";
  case LanguageID::hu:
    return "hu";
  case LanguageID::is:
    return "is";
  case LanguageID::it:
    return "it";
  case LanguageID::ja:
    return "ja";
  case LanguageID::ko:
    return "ko";
  case LanguageID::nl:
    return "nl";
  case LanguageID::no:
    return "no";
  case LanguageID::pl:
    return "pl";
  case LanguageID::pt:
    return "pt";
  case LanguageID::rm:
    return "rm";
  case LanguageID::ro:
    return "ro";
  case LanguageID::ru:
    return "ru";
  case LanguageID::hr:
    return "hr";
  case LanguageID::sk:
    return "sk";
  case LanguageID::sq:
    return "sq";
  case LanguageID::sv:
    return "sv";
  case LanguageID::th:
    return "th";
  case LanguageID::tr:
    return "tr";
  case LanguageID::ur:
    return "ur";
  case LanguageID::id:
    return "id";
  case LanguageID::uk:
    return "uk";
  case LanguageID::be:
    return "be";
  case LanguageID::sl:
    return "sl";
  case LanguageID::et:
    return "et";
  case LanguageID::lv:
    return "lv";
  case LanguageID::lt:
    return "lt";
  case LanguageID::tg:
    return "tg";
  case LanguageID::fa:
    return "fa";
  case LanguageID::vi:
    return "vi";
  case LanguageID::hy:
    return "hy";
  case LanguageID::az:
    return "az";
  case LanguageID::eu:
    return "eu";
  case LanguageID::hsb:
    return "hsb";
  case LanguageID::mk:
    return "mk";
  case LanguageID::st:
    return "st";
  case LanguageID::ts:
    return "ts";
  case LanguageID::tn:
    return "tn";
  case LanguageID::ve:
    return "ve";
  case LanguageID::xh:
    return "xh";
  case LanguageID::zu:
    return "zu";
  case LanguageID::af:
    return "af";
  case LanguageID::ka:
    return "ka";
  case LanguageID::fo:
    return "fo";
  case LanguageID::hi:
    return "hi";
  case LanguageID::mt:
    return "mt";
  case LanguageID::se:
    return "se";
  case LanguageID::ga:
    return "ga";
  case LanguageID::yi:
    return "yi, reserved";
  case LanguageID::ms:
    return "ms";
  case LanguageID::kk:
    return "kk";
  case LanguageID::ky:
    return "ky";
  case LanguageID::sw:
    return "sw";
  case LanguageID::tk:
    return "tk";
  case LanguageID::uz:
    return "uz";
  case LanguageID::tt:
    return "tt";
  case LanguageID::bn:
    return "bn";
  case LanguageID::pa:
    return "pa";
  case LanguageID::gu:
    return "gu";
  case LanguageID::l_or:
    return "or";
  case LanguageID::ta:
    return "ta";
  case LanguageID::te:
    return "te";
  case LanguageID::kn:
    return "kn";
  case LanguageID::ml:
    return "ml";
  case LanguageID::as:
    return "as";
  case LanguageID::mr:
    return "mr";
  case LanguageID::sa:
    return "sa";
  case LanguageID::mn:
    return "mn";
  case LanguageID::bo:
    return "bo";
  case LanguageID::cy:
    return "cy";
  case LanguageID::km:
    return "km";
  case LanguageID::lo:
    return "lo";
  case LanguageID::my:
    return "my";
  case LanguageID::gl:
    return "gl";
  case LanguageID::kok:
    return "kok";
  case LanguageID::mni:
    return "mni, reserved";
  case LanguageID::sd:
    return "sd";
  case LanguageID::syr:
    return "syr";
  case LanguageID::si:
    return "si";
  case LanguageID::chr:
    return "chr";
  case LanguageID::iu:
    return "iu";
  case LanguageID::am:
    return "am";
  case LanguageID::tzm:
    return "tzm";
  case LanguageID::ks:
    return "ks";
  case LanguageID::ne:
    return "ne";
  case LanguageID::fy:
    return "fy";
  case LanguageID::ps:
    return "ps";
  case LanguageID::fil:
    return "fil";
  case LanguageID::dv:
    return "dv";
  case LanguageID::bin:
    return "bin, reserved";
  case LanguageID::ff:
    return "ff";
  case LanguageID::ha:
    return "ha";
  case LanguageID::ibb:
    return "ibb, reserved";
  case LanguageID::yo:
    return "yo";
  case LanguageID::quz:
    return "quz";
  case LanguageID::nso:
    return "nso";
  case LanguageID::ba:
    return "ba";
  case LanguageID::lb:
    return "lb";
  case LanguageID::kl:
    return "kl";
  case LanguageID::ig:
    return "ig";
  case LanguageID::kr:
    return "kr, reserved";
  case LanguageID::om:
    return "om";
  case LanguageID::ti:
    return "ti";
  case LanguageID::gn:
    return "gn";
  case LanguageID::haw:
    return "haw";
  case LanguageID::la:
    return "la, reserved";
  case LanguageID::so:
    return "so, reserved";
  case LanguageID::ii:
    return "ii";
  case LanguageID::pap:
    return "pap, reserved";
  case LanguageID::arn:
    return "arn";
  case LanguageID::moh:
    return "moh";
  case LanguageID::br:
    return "br";
  case LanguageID::invariant:
    return "invariant";
  case LanguageID::ug:
    return "ug";
  case LanguageID::mi:
    return "mi";
  case LanguageID::oc:
    return "oc";
  case LanguageID::co:
    return "co";
  case LanguageID::gsw:
    return "gsw";
  case LanguageID::sah:
    return "sah";
  case LanguageID::qut:
    return "qut";
  case LanguageID::rw:
    return "rw";
  case LanguageID::wo:
    return "wo";
  case LanguageID::prs:
    return "prs";
  case LanguageID::gd:
    return "gd";
  case LanguageID::ku:
    return "ku";
  case LanguageID::quc:
    return "quc, reserved";
  case LanguageID::ar_SA:
    return "ar-SA";
  case LanguageID::bg_BG:
    return "bg-BG";
  case LanguageID::ca_ES:
    return "ca-ES";
  case LanguageID::zh_TW:
    return "zh-TW";
  case LanguageID::cs_CZ:
    return "cs-CZ";
  case LanguageID::da_DK:
    return "da-DK";
  case LanguageID::de_DE:
    return "de-DE";
  case LanguageID::el_GR:
    return "el-GR";
  case LanguageID::en_US:
    return "en-US";
  case LanguageID::es_ES_tradnl:
    return "es-ES_tradnl";
  case LanguageID::fi_FI:
    return "fi-FI";
  case LanguageID::fr_FR:
    return "fr-FR";
  case LanguageID::he_IL:
    return "he-IL";
  case LanguageID::hu_HU:
    return "hu-HU";
  case LanguageID::is_IS:
    return "is-IS";
  case LanguageID::it_IT:
    return "it-IT";
  case LanguageID::ja_JP:
    return "ja-JP";
  case LanguageID::ko_KR:
    return "ko-KR";
  case LanguageID::nl_NL:
    return "nl-NL";
  case LanguageID::nb_NO:
    return "nb-NO";
  case LanguageID::pl_PL:
    return "pl-PL";
  case LanguageID::pt_BR:
    return "pt-BR";
  case LanguageID::rm_CH:
    return "rm-CH";
  case LanguageID::ro_RO:
    return "ro-RO";
  case LanguageID::ru_RU:
    return "ru-RU";
  case LanguageID::hr_HR:
    return "hr-HR";
  case LanguageID::sk_SK:
    return "sk-SK";
  case LanguageID::sq_AL:
    return "sq-AL";
  case LanguageID::sv_SE:
    return "sv-SE";
  case LanguageID::th_TH:
    return "th-TH";
  case LanguageID::tr_TR:
    return "tr-TR";
  case LanguageID::ur_PK:
    return "ur-PK";
  case LanguageID::id_ID:
    return "id-ID";
  case LanguageID::uk_UA:
    return "uk-UA";
  case LanguageID::be_BY:
    return "be-BY";
  case LanguageID::sl_SI:
    return "sl-SI";
  case LanguageID::et_EE:
    return "et-EE";
  case LanguageID::lv_LV:
    return "lv-LV";
  case LanguageID::lt_LT:
    return "lt-LT";
  case LanguageID::tg_Cyrl_TJ:
    return "tg-Cyrl-TJ";
  case LanguageID::fa_IR:
    return "fa-IR";
  case LanguageID::vi_VN:
    return "vi-VN";
  case LanguageID::hy_AM:
    return "hy-AM";
  case LanguageID::az_Latn_AZ:
    return "az-Latn-AZ";
  case LanguageID::eu_ES:
    return "eu-ES";
  case LanguageID::hsb_DE:
    return "hsb-DE";
  case LanguageID::mk_MK:
    return "mk-MK";
  case LanguageID::st_ZA:
    return "st-ZA";
  case LanguageID::ts_ZA:
    return "ts-ZA";
  case LanguageID::tn_ZA:
    return "tn-ZA";
  case LanguageID::ve_ZA:
    return "ve-ZA";
  case LanguageID::xh_ZA:
    return "xh-ZA";
  case LanguageID::zu_ZA:
    return "zu-ZA";
  case LanguageID::af_ZA:
    return "af-ZA";
  case LanguageID::ka_GE:
    return "ka-GE";
  case LanguageID::fo_FO:
    return "fo-FO";
  case LanguageID::hi_IN:
    return "hi-IN";
  case LanguageID::mt_MT:
    return "mt-MT";
  case LanguageID::se_NO:
    return "se-NO";
  case LanguageID::yi_Hebr:
    return "yi-Hebr, reserved";
  case LanguageID::ms_MY:
    return "ms-MY";
  case LanguageID::kk_KZ:
    return "kk-KZ";
  case LanguageID::ky_KG:
    return "ky-KG";
  case LanguageID::sw_KE:
    return "sw-KE";
  case LanguageID::tk_TM:
    return "tk-TM";
  case LanguageID::uz_Latn_UZ:
    return "uz-Latn-UZ";
  case LanguageID::tt_RU:
    return "tt-RU";
  case LanguageID::bn_IN:
    return "bn-IN";
  case LanguageID::pa_IN:
    return "pa-IN";
  case LanguageID::gu_IN:
    return "gu-IN";
  case LanguageID::or_IN:
    return "or-IN";
  case LanguageID::ta_IN:
    return "ta-IN";
  case LanguageID::te_IN:
    return "te-IN";
  case LanguageID::kn_IN:
    return "kn-IN";
  case LanguageID::ml_IN:
    return "ml-IN";
  case LanguageID::as_IN:
    return "as-IN";
  case LanguageID::mr_IN:
    return "mr-IN";
  case LanguageID::sa_IN:
    return "sa-IN";
  case LanguageID::mn_MN:
    return "mn-MN";
  case LanguageID::bo_CN:
    return "bo-CN";
  case LanguageID::cy_GB:
    return "cy-GB";
  case LanguageID::km_KH:
    return "km-KH";
  case LanguageID::lo_LA:
    return "lo-LA";
  case LanguageID::my_MM:
    return "my-MM";
  case LanguageID::gl_ES:
    return "gl-ES";
  case LanguageID::kok_IN:
    return "kok-IN";
  case LanguageID::mni_IN:
    return "mni-IN, reserved";
  case LanguageID::sd_Deva_IN:
    return "sd-Deva-IN, reserved";
  case LanguageID::syr_SY:
    return "syr-SY";
  case LanguageID::si_LK:
    return "si-LK";
  case LanguageID::chr_Cher_US:
    return "chr-Cher-US";
  case LanguageID::iu_Cans_CA:
    return "iu-Cans-CA";
  case LanguageID::am_ET:
    return "am-ET";
  case LanguageID::tzm_Arab_MA:
    return "tzm-Arab-MA, reserved";
  case LanguageID::ks_Arab:
    return "ks-Arab";
  case LanguageID::ne_NP:
    return "ne-NP";
  case LanguageID::fy_NL:
    return "fy-NL";
  case LanguageID::ps_AF:
    return "ps-AF";
  case LanguageID::fil_PH:
    return "fil-PH";
  case LanguageID::dv_MV:
    return "dv-MV";
  case LanguageID::bin_NG:
    return "bin-NG, reserved";
  case LanguageID::fuv_NG:
    return "fuv-NG, reserved";
  case LanguageID::ha_Latn_NG:
    return "ha-Latn-NG";
  case LanguageID::ibb_NG:
    return "ibb-NG, reserved";
  case LanguageID::yo_NG:
    return "yo-NG";
  case LanguageID::quz_BO:
    return "quz-BO";
  case LanguageID::nso_ZA:
    return "nso-ZA";
  case LanguageID::ba_RU:
    return "ba-RU";
  case LanguageID::lb_LU:
    return "lb-LU";
  case LanguageID::kl_GL:
    return "kl-GL";
  case LanguageID::ig_NG:
    return "ig-NG";
  case LanguageID::kr_NG:
    return "kr-NG, reserved";
  case LanguageID::om_ET:
    return "om-ET";
  case LanguageID::ti_ET:
    return "ti-ET";
  case LanguageID::gn_PY:
    return "gn-PY";
  case LanguageID::haw_US:
    return "haw-US";
  case LanguageID::la_Latn:
    return "la-Latn, reserved";
  case LanguageID::so_SO:
    return "so-SO";
  case LanguageID::ii_CN:
    return "ii-CN";
  case LanguageID::pap_029:
    return "pap-029, reserved";
  case LanguageID::arn_CL:
    return "arn-CL";
  case LanguageID::moh_CA:
    return "moh-CA";
  case LanguageID::br_FR:
    return "br-FR";
  case LanguageID::ug_CN:
    return "ug-CN";
  case LanguageID::mi_NZ:
    return "mi-NZ";
  case LanguageID::oc_FR:
    return "oc-FR";
  case LanguageID::co_FR:
    return "co-FR";
  case LanguageID::gsw_FR:
    return "gsw-FR";
  case LanguageID::sah_RU:
    return "sah-RU";
  case LanguageID::qut_GT:
    return "qut-GT";
  case LanguageID::rw_RW:
    return "rw-RW";
  case LanguageID::wo_SN:
    return "wo-SN";
  case LanguageID::prs_AF:
    return "prs-AF";
  case LanguageID::plt_MG:
    return "plt-MG, reserved";
  case LanguageID::zh_yue_HK:
    return "zh-yue-HK, reserved";
  case LanguageID::tdd_Tale_CN:
    return "tdd-Tale-CN, reserved";
  case LanguageID::khb_Talu_CN:
    return "khb-Talu-CN, reserved";
  case LanguageID::gd_GB:
    return "gd-GB";
  case LanguageID::ku_Arab_IQ:
    return "ku-Arab-IQ";
  case LanguageID::quc_CO:
    return "quc-CO, reserved";
  case LanguageID::qps_ploc:
    return "qps-ploc";
  case LanguageID::qps_ploca:
    return "qps-ploca";
  case LanguageID::ar_IQ:
    return "ar-IQ";
  case LanguageID::ca_ES_valencia:
    return "ca-ES-valencia";
  case LanguageID::zh_CN:
    return "zh-CN";
  case LanguageID::de_CH:
    return "de-CH";
  case LanguageID::en_GB:
    return "en-GB";
  case LanguageID::es_MX:
    return "es-MX";
  case LanguageID::fr_BE:
    return "fr-BE";
  case LanguageID::it_CH:
    return "it-CH";
  case LanguageID::ja_Ploc_JP:
    return "ja-Ploc-JP, reserved";
  case LanguageID::nl_BE:
    return "nl-BE";
  case LanguageID::nn_NO:
    return "nn-NO";
  case LanguageID::pt_PT:
    return "pt-PT";
  case LanguageID::ro_MD:
    return "ro-MD";
  case LanguageID::ru_MD:
    return "ru-MD";
  case LanguageID::sr_Latn_CS:
    return "sr-Latn-CS";
  case LanguageID::sv_FI:
    return "sv-FI";
  case LanguageID::ur_IN:
    return "ur-IN";
  case LanguageID::az_Cyrl_AZ:
    return "az-Cyrl-AZ";
  case LanguageID::dsb_DE:
    return "dsb-DE";
  case LanguageID::tn_BW:
    return "tn-BW";
  case LanguageID::se_SE:
    return "se-SE";
  case LanguageID::ga_IE:
    return "ga-IE";
  case LanguageID::ms_BN:
    return "ms-BN";
  case LanguageID::kk_Latn_KZ:
    return "kk-Latn-KZ, reserved";
  case LanguageID::uz_Cyrl_UZ:
    return "uz-Cyrl-UZ";
  case LanguageID::bn_BD:
    return "bn-BD";
  case LanguageID::pa_Arab_PK:
    return "pa-Arab-PK";
  case LanguageID::ta_LK:
    return "ta-LK";
  case LanguageID::mn_Mong_CN:
    return "mn-Mong-CN";
  case LanguageID::bo_BT:
    return "bo-BT, reserved";
  case LanguageID::sd_Arab_PK:
    return "sd-Arab-PK";
  case LanguageID::iu_Latn_CA:
    return "iu-Latn-CA";
  case LanguageID::tzm_Latn_DZ:
    return "tzm-Latn-DZ";
  case LanguageID::ks_Deva:
    return "ks-Deva, reserved";
  case LanguageID::ne_IN:
    return "ne-IN";
  case LanguageID::ff_Latn_SN:
    return "ff-Latn-SN";
  case LanguageID::quz_EC:
    return "quz-EC";
  case LanguageID::ti_ER:
    return "ti-ER";
  case LanguageID::qps_plocm:
    return "qps-plocm";
  case LanguageID::ar_EG:
    return "ar-EG";
  case LanguageID::zh_HK:
    return "zh-HK";
  case LanguageID::de_AT:
    return "de-AT";
  case LanguageID::en_AU:
    return "en-AU";
  case LanguageID::es_ES:
    return "es-ES";
  case LanguageID::fr_CA:
    return "fr-CA";
  case LanguageID::sr_Cyrl_CS:
    return "sr-Cyrl-CS";
  case LanguageID::se_FI:
    return "se-FI";
  case LanguageID::mn_Mong_MN:
    return "mn-Mong-MN";
  case LanguageID::dz_BT:
    return "dz-BT";
  case LanguageID::tmz_MA:
    return "tmz-MA, reserved";
  case LanguageID::quz_PE:
    return "quz-PE";
  case LanguageID::ar_LY:
    return "ar-LY";
  case LanguageID::zh_SG:
    return "zh-SG";
  case LanguageID::de_LU:
    return "de-LU";
  case LanguageID::en_CA:
    return "en-CA";
  case LanguageID::es_GT:
    return "es-GT";
  case LanguageID::fr_CH:
    return "fr-CH";
  case LanguageID::hr_BA:
    return "hr-BA";
  case LanguageID::smj_NO:
    return "smj-NO";
  case LanguageID::tzm_Tfng_MA:
    return "tzm-Tfng-MA";
  case LanguageID::ar_DZ:
    return "ar-DZ";
  case LanguageID::zh_MO:
    return "zh-MO";
  case LanguageID::de_LI:
    return "de-LI";
  case LanguageID::en_NZ:
    return "en-NZ";
  case LanguageID::es_CR:
    return "es-CR";
  case LanguageID::fr_LU:
    return "fr-LU";
  case LanguageID::bs_Latn_BA:
    return "bs-Latn-BA";
  case LanguageID::smj_SE:
    return "smj-SE";
  case LanguageID::ar_MA:
    return "ar-MA";
  case LanguageID::en_IE:
    return "en-IE";
  case LanguageID::es_PA:
    return "es-PA";
  case LanguageID::fr_MC:
    return "fr-MC";
  case LanguageID::sr_Latn_BA:
    return "sr-Latn-BA";
  case LanguageID::sma_NO:
    return "sma-NO";
  case LanguageID::ar_TN:
    return "ar-TN";
  case LanguageID::en_ZA:
    return "en-ZA";
  case LanguageID::es_DO:
    return "es-DO";
  case LanguageID::sr_Cyrl_BA:
    return "sr-Cyrl-BA";
  case LanguageID::sma_SE:
    return "sma-SE";
  case LanguageID::ar_OM:
    return "ar-OM";
  case LanguageID::en_JM:
    return "en-JM";
  case LanguageID::es_VE:
    return "es-VE";
  case LanguageID::fr_RE:
    return "fr-RE";
  case LanguageID::bs_Cyrl_BA:
    return "bs-Cyrl-BA";
  case LanguageID::sms_FI:
    return "sms-FI";
  case LanguageID::ar_YE:
    return "ar-YE";
  case LanguageID::en_029:
    return "en-029";
  case LanguageID::es_CO:
    return "es-CO";
  case LanguageID::fr_CD:
    return "fr-CD";
  case LanguageID::sr_Latn_RS:
    return "sr-Latn-RS";
  case LanguageID::smn_FI:
    return "smn-FI";
  case LanguageID::ar_SY:
    return "ar-SY";
  case LanguageID::en_BZ:
    return "en-BZ";
  case LanguageID::es_PE:
    return "es-PE";
  case LanguageID::fr_SN:
    return "fr-SN";
  case LanguageID::sr_Cyrl_RS:
    return "sr-Cyrl-RS";
  case LanguageID::ar_JO:
    return "ar-JO";
  case LanguageID::en_TT:
    return "en-TT";
  case LanguageID::es_AR:
    return "es-AR";
  case LanguageID::fr_CM:
    return "fr-CM";
  case LanguageID::sr_Latn_ME:
    return "sr-Latn-ME";
  case LanguageID::ar_LB:
    return "ar-LB";
  case LanguageID::en_ZW:
    return "en-ZW";
  case LanguageID::es_EC:
    return "es-EC";
  case LanguageID::fr_CI:
    return "fr-CI";
  case LanguageID::sr_Cyrl_ME:
    return "sr-Cyrl-ME";
  case LanguageID::ar_KW:
    return "ar-KW";
  case LanguageID::en_PH:
    return "en-PH";
  case LanguageID::es_CL:
    return "es-CL";
  case LanguageID::fr_ML:
    return "fr-ML";
  case LanguageID::ar_AE:
    return "ar-AE";
  case LanguageID::en_ID:
    return "en-ID, reserved";
  case LanguageID::es_UY:
    return "es-UY";
  case LanguageID::fr_MA:
    return "fr-MA";
  case LanguageID::ar_BH:
    return "ar-BH";
  case LanguageID::en_HK:
    return "en-HK";
  case LanguageID::es_PY:
    return "es-PY";
  case LanguageID::fr_HT:
    return "fr-HT";
  case LanguageID::ar_QA:
    return "ar-QA";
  case LanguageID::en_IN:
    return "en-IN";
  case LanguageID::es_BO:
    return "es-BO";
  case LanguageID::ar_Ploc_SA:
    return "ar-Ploc-SA, reserved";
  case LanguageID::en_MY:
    return "en-MY";
  case LanguageID::es_SV:
    return "es-SV";
  case LanguageID::ar_145:
    return "ar-145, reserved";
  case LanguageID::en_SG:
    return "en-SG";
  case LanguageID::es_HN:
    return "es-HN";
  case LanguageID::en_AE:
    return "en-AE";
  case LanguageID::es_NI:
    return "es-NI";
  case LanguageID::en_BH:
    return "en-BH, reserved";
  case LanguageID::es_PR:
    return "es-PR";
  case LanguageID::en_EG:
    return "en-EG, reserved";
  case LanguageID::es_US:
    return "es-US";
  case LanguageID::en_JO:
    return "en-JO, reserved";
  case LanguageID::es_419:
    return "es-419";
  case LanguageID::en_KW:
    return "en-KW, reserved";
  case LanguageID::es_CU:
    return "es-CU";
  case LanguageID::en_TR:
    return "en-TR, reserved";
  case LanguageID::en_YE:
    return "en-YE, reserved";
  case LanguageID::bs_Cyrl:
    return "bs-Cyrl";
  case LanguageID::bs_Latn:
    return "bs-Latn";
  case LanguageID::sr_Cyrl:
    return "sr-Cyrl";
  case LanguageID::sr_Latn:
    return "sr-Latn";
  case LanguageID::smn:
    return "smn";
  case LanguageID::az_Cyrl:
    return "az-Cyrl";
  case LanguageID::sms:
    return "sms";
  case LanguageID::zh:
    return "zh";
  case LanguageID::nn:
    return "nn";
  case LanguageID::bs:
    return "bs";
  case LanguageID::az_Latn:
    return "az-Latn";
  case LanguageID::sma:
    return "sma";
  case LanguageID::kk_Cyrl:
    return "kk-Cyrl, reserved";
  case LanguageID::uz_Cyrl:
    return "uz-Cyrl";
  case LanguageID::mn_Cyrl:
    return "mn-Cyrl";
  case LanguageID::iu_Cans:
    return "iu-Cans";
  case LanguageID::tzm_Tfng:
    return "tzm-Tfng";
  case LanguageID::zh_Hant:
    return "zh-Hant";
  case LanguageID::nb:
    return "nb";
  case LanguageID::sr:
    return "sr";
  case LanguageID::tg_Cyrl:
    return "tg-Cyrl";
  case LanguageID::dsb:
    return "dsb";
  case LanguageID::smj:
    return "smj";
  case LanguageID::kk_Latn:
    return "kk-Latn, reserved";
  case LanguageID::uz_Latn:
    return "uz-Latn";
  case LanguageID::pa_Arab:
    return "pa-Arab";
  case LanguageID::mn_Mong:
    return "mn-Mong";
  case LanguageID::sd_Arab:
    return "sd-Arab";
  case LanguageID::chr_Cher:
    return "chr-Cher";
  case LanguageID::iu_Latn:
    return "iu-Latn";
  case LanguageID::tzm_Latn:
    return "tzm-Latn";
  case LanguageID::ff_Latn:
    return "ff-Latn";
  case LanguageID::ha_Latn:
    return "ha-Latn";
  case LanguageID::ku_Arab:
    return "ku-Arab";
  case LanguageID::reservedF2EE:
    return "reserved";
  case LanguageID::fr_015:
    return "fr-015, reserved";
  case LanguageID::reservedEEEE:
    return "reserved";
  case LanguageID::invalid:
    return "invalid";
  default:
    return "unspecified";
  }
}


} // namespace MSONcommon
