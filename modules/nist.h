#pragma once

#include "essentials.h"

namespace nist {
	// NOTE: Below, the atomic mass unit (amu), or unified atomic mass unit,
	// is referred to as atomic mass. Likewise, the atomic unit of mass is
	// simply named the atomic unit, whereas atomic units of energy and
	// length are referred to as Hartree and Bohr.

	static constexpr f64 INVERSE_FINE_STRUCT = 137.035999084;

	static constexpr f64 BOHR_RADIUS = 5.29177210903E-11;  // m

	static constexpr f64 RYDBERG_CONST = 10973731.568160;  // 1/m

	static constexpr f64 BOLTZMANN_CONST = 1.380649E-23;   // J/K

	static constexpr f64 AVOGADRO_CONST = 6.02214076E23;   // 1/mol

	static constexpr f64 ELECTRON_MASS = 9.1093837015E-31; // Kg

	static constexpr f64 PROTON_MASS = 1.67262192369E-27;  // Kg

	static constexpr f64 PROTON_TO_ELECTRON_RATIO = PROTON_MASS/ELECTRON_MASS;

	static constexpr f64 BOHR_TO_METER = BOHR_RADIUS;

	static constexpr f64 HARTREE_TO_EV = 27.211386245988;

	static constexpr f64 HARTREE_TO_WAVENUM = 219474.63137054;

	static constexpr f64 HARTREE_TO_JOULE = 4.3597447222071E-18;

	static constexpr f64 KILOGRAM_TO_ATOMIC_MASS = 1000.0*AVOGADRO_CONST;

	static constexpr f64 ATOMIC_MASS_TO_ATOMIC_UNIT = 1.0/(ELECTRON_MASS*KILOGRAM_TO_ATOMIC_MASS);

	enum class Isotope: u16 {
		atom_1H = 0,
		atom_2H,
		atom_3H,
		atom_4H,
		atom_5H,
		atom_6H,
		atom_7H,
		atom_3He,
		atom_4He,
		atom_5He,
		atom_6He,
		atom_7He,
		atom_8He,
		atom_9He,
		atom_10He,
		atom_3Li,
		atom_4Li,
		atom_5Li,
		atom_6Li,
		atom_7Li,
		atom_8Li,
		atom_9Li,
		atom_10Li,
		atom_11Li,
		atom_12Li,
		atom_13Li,
		atom_5Be,
		atom_6Be,
		atom_7Be,
		atom_8Be,
		atom_9Be,
		atom_10Be,
		atom_11Be,
		atom_12Be,
		atom_13Be,
		atom_14Be,
		atom_15Be,
		atom_16Be,
		atom_6B,
		atom_7B,
		atom_8B,
		atom_9B,
		atom_10B,
		atom_11B,
		atom_12B,
		atom_13B,
		atom_14B,
		atom_15B,
		atom_16B,
		atom_17B,
		atom_18B,
		atom_19B,
		atom_20B,
		atom_21B,
		atom_8C,
		atom_9C,
		atom_10C,
		atom_11C,
		atom_12C,
		atom_13C,
		atom_14C,
		atom_15C,
		atom_16C,
		atom_17C,
		atom_18C,
		atom_19C,
		atom_20C,
		atom_21C,
		atom_22C,
		atom_23C,
		atom_10N,
		atom_11N,
		atom_12N,
		atom_13N,
		atom_14N,
		atom_15N,
		atom_16N,
		atom_17N,
		atom_18N,
		atom_19N,
		atom_20N,
		atom_21N,
		atom_22N,
		atom_23N,
		atom_24N,
		atom_25N,
		atom_12O,
		atom_13O,
		atom_14O,
		atom_15O,
		atom_16O,
		atom_17O,
		atom_18O,
		atom_19O,
		atom_20O,
		atom_21O,
		atom_22O,
		atom_23O,
		atom_24O,
		atom_25O,
		atom_26O,
		atom_27O,
		atom_28O,
		atom_14F,
		atom_15F,
		atom_16F,
		atom_17F,
		atom_18F,
		atom_19F,
		atom_20F,
		atom_21F,
		atom_22F,
		atom_23F,
		atom_24F,
		atom_25F,
		atom_26F,
		atom_27F,
		atom_28F,
		atom_29F,
		atom_30F,
		atom_31F,
		atom_16Ne,
		atom_17Ne,
		atom_18Ne,
		atom_19Ne,
		atom_20Ne,
		atom_21Ne,
		atom_22Ne,
		atom_23Ne,
		atom_24Ne,
		atom_25Ne,
		atom_26Ne,
		atom_27Ne,
		atom_28Ne,
		atom_29Ne,
		atom_30Ne,
		atom_31Ne,
		atom_32Ne,
		atom_33Ne,
		atom_34Ne,
		atom_18Na,
		atom_19Na,
		atom_20Na,
		atom_21Na,
		atom_22Na,
		atom_23Na,
		atom_24Na,
		atom_25Na,
		atom_26Na,
		atom_27Na,
		atom_28Na,
		atom_29Na,
		atom_30Na,
		atom_31Na,
		atom_32Na,
		atom_33Na,
		atom_34Na,
		atom_35Na,
		atom_36Na,
		atom_37Na,
		atom_19Mg,
		atom_20Mg,
		atom_21Mg,
		atom_22Mg,
		atom_23Mg,
		atom_24Mg,
		atom_25Mg,
		atom_26Mg,
		atom_27Mg,
		atom_28Mg,
		atom_29Mg,
		atom_30Mg,
		atom_31Mg,
		atom_32Mg,
		atom_33Mg,
		atom_34Mg,
		atom_35Mg,
		atom_36Mg,
		atom_37Mg,
		atom_38Mg,
		atom_39Mg,
		atom_40Mg,
		atom_21Al,
		atom_22Al,
		atom_23Al,
		atom_24Al,
		atom_25Al,
		atom_26Al,
		atom_27Al,
		atom_28Al,
		atom_29Al,
		atom_30Al,
		atom_31Al,
		atom_32Al,
		atom_33Al,
		atom_34Al,
		atom_35Al,
		atom_36Al,
		atom_37Al,
		atom_38Al,
		atom_39Al,
		atom_40Al,
		atom_41Al,
		atom_42Al,
		atom_43Al,
		atom_22Si,
		atom_23Si,
		atom_24Si,
		atom_25Si,
		atom_26Si,
		atom_27Si,
		atom_28Si,
		atom_29Si,
		atom_30Si,
		atom_31Si,
		atom_32Si,
		atom_33Si,
		atom_34Si,
		atom_35Si,
		atom_36Si,
		atom_37Si,
		atom_38Si,
		atom_39Si,
		atom_40Si,
		atom_41Si,
		atom_42Si,
		atom_43Si,
		atom_44Si,
		atom_45Si,
		atom_24P,
		atom_25P,
		atom_26P,
		atom_27P,
		atom_28P,
		atom_29P,
		atom_30P,
		atom_31P,
		atom_32P,
		atom_33P,
		atom_34P,
		atom_35P,
		atom_36P,
		atom_37P,
		atom_38P,
		atom_39P,
		atom_40P,
		atom_41P,
		atom_42P,
		atom_43P,
		atom_44P,
		atom_45P,
		atom_46P,
		atom_47P,
		atom_26S,
		atom_27S,
		atom_28S,
		atom_29S,
		atom_30S,
		atom_31S,
		atom_32S,
		atom_33S,
		atom_34S,
		atom_35S,
		atom_36S,
		atom_37S,
		atom_38S,
		atom_39S,
		atom_40S,
		atom_41S,
		atom_42S,
		atom_43S,
		atom_44S,
		atom_45S,
		atom_46S,
		atom_47S,
		atom_48S,
		atom_49S,
		atom_28Cl,
		atom_29Cl,
		atom_30Cl,
		atom_31Cl,
		atom_32Cl,
		atom_33Cl,
		atom_34Cl,
		atom_35Cl,
		atom_36Cl,
		atom_37Cl,
		atom_38Cl,
		atom_39Cl,
		atom_40Cl,
		atom_41Cl,
		atom_42Cl,
		atom_43Cl,
		atom_44Cl,
		atom_45Cl,
		atom_46Cl,
		atom_47Cl,
		atom_48Cl,
		atom_49Cl,
		atom_50Cl,
		atom_51Cl,
		atom_30Ar,
		atom_31Ar,
		atom_32Ar,
		atom_33Ar,
		atom_34Ar,
		atom_35Ar,
		atom_36Ar,
		atom_37Ar,
		atom_38Ar,
		atom_39Ar,
		atom_40Ar,
		atom_41Ar,
		atom_42Ar,
		atom_43Ar,
		atom_44Ar,
		atom_45Ar,
		atom_46Ar,
		atom_47Ar,
		atom_48Ar,
		atom_49Ar,
		atom_50Ar,
		atom_51Ar,
		atom_52Ar,
		atom_53Ar,
		atom_32K,
		atom_33K,
		atom_34K,
		atom_35K,
		atom_36K,
		atom_37K,
		atom_38K,
		atom_39K,
		atom_40K,
		atom_41K,
		atom_42K,
		atom_43K,
		atom_44K,
		atom_45K,
		atom_46K,
		atom_47K,
		atom_48K,
		atom_49K,
		atom_50K,
		atom_51K,
		atom_52K,
		atom_53K,
		atom_54K,
		atom_55K,
		atom_56K,
		atom_34Ca,
		atom_35Ca,
		atom_36Ca,
		atom_37Ca,
		atom_38Ca,
		atom_39Ca,
		atom_40Ca,
		atom_41Ca,
		atom_42Ca,
		atom_43Ca,
		atom_44Ca,
		atom_45Ca,
		atom_46Ca,
		atom_47Ca,
		atom_48Ca,
		atom_49Ca,
		atom_50Ca,
		atom_51Ca,
		atom_52Ca,
		atom_53Ca,
		atom_54Ca,
		atom_55Ca,
		atom_56Ca,
		atom_57Ca,
		atom_58Ca,
		atom_36Sc,
		atom_37Sc,
		atom_38Sc,
		atom_39Sc,
		atom_40Sc,
		atom_41Sc,
		atom_42Sc,
		atom_43Sc,
		atom_44Sc,
		atom_45Sc,
		atom_46Sc,
		atom_47Sc,
		atom_48Sc,
		atom_49Sc,
		atom_50Sc,
		atom_51Sc,
		atom_52Sc,
		atom_53Sc,
		atom_54Sc,
		atom_55Sc,
		atom_56Sc,
		atom_57Sc,
		atom_58Sc,
		atom_59Sc,
		atom_60Sc,
		atom_61Sc,
		atom_38Ti,
		atom_39Ti,
		atom_40Ti,
		atom_41Ti,
		atom_42Ti,
		atom_43Ti,
		atom_44Ti,
		atom_45Ti,
		atom_46Ti,
		atom_47Ti,
		atom_48Ti,
		atom_49Ti,
		atom_50Ti,
		atom_51Ti,
		atom_52Ti,
		atom_53Ti,
		atom_54Ti,
		atom_55Ti,
		atom_56Ti,
		atom_57Ti,
		atom_58Ti,
		atom_59Ti,
		atom_60Ti,
		atom_61Ti,
		atom_62Ti,
		atom_63Ti,
		atom_40V,
		atom_41V,
		atom_42V,
		atom_43V,
		atom_44V,
		atom_45V,
		atom_46V,
		atom_47V,
		atom_48V,
		atom_49V,
		atom_50V,
		atom_51V,
		atom_52V,
		atom_53V,
		atom_54V,
		atom_55V,
		atom_56V,
		atom_57V,
		atom_58V,
		atom_59V,
		atom_60V,
		atom_61V,
		atom_62V,
		atom_63V,
		atom_64V,
		atom_65V,
		atom_66V,
		atom_42Cr,
		atom_43Cr,
		atom_44Cr,
		atom_45Cr,
		atom_46Cr,
		atom_47Cr,
		atom_48Cr,
		atom_49Cr,
		atom_50Cr,
		atom_51Cr,
		atom_52Cr,
		atom_53Cr,
		atom_54Cr,
		atom_55Cr,
		atom_56Cr,
		atom_57Cr,
		atom_58Cr,
		atom_59Cr,
		atom_60Cr,
		atom_61Cr,
		atom_62Cr,
		atom_63Cr,
		atom_64Cr,
		atom_65Cr,
		atom_66Cr,
		atom_67Cr,
		atom_68Cr,
		atom_44Mn,
		atom_45Mn,
		atom_46Mn,
		atom_47Mn,
		atom_48Mn,
		atom_49Mn,
		atom_50Mn,
		atom_51Mn,
		atom_52Mn,
		atom_53Mn,
		atom_54Mn,
		atom_55Mn,
		atom_56Mn,
		atom_57Mn,
		atom_58Mn,
		atom_59Mn,
		atom_60Mn,
		atom_61Mn,
		atom_62Mn,
		atom_63Mn,
		atom_64Mn,
		atom_65Mn,
		atom_66Mn,
		atom_67Mn,
		atom_68Mn,
		atom_69Mn,
		atom_70Mn,
		atom_71Mn,
		atom_45Fe,
		atom_46Fe,
		atom_47Fe,
		atom_48Fe,
		atom_49Fe,
		atom_50Fe,
		atom_51Fe,
		atom_52Fe,
		atom_53Fe,
		atom_54Fe,
		atom_55Fe,
		atom_56Fe,
		atom_57Fe,
		atom_58Fe,
		atom_59Fe,
		atom_60Fe,
		atom_61Fe,
		atom_62Fe,
		atom_63Fe,
		atom_64Fe,
		atom_65Fe,
		atom_66Fe,
		atom_67Fe,
		atom_68Fe,
		atom_69Fe,
		atom_70Fe,
		atom_71Fe,
		atom_72Fe,
		atom_73Fe,
		atom_74Fe,
		atom_47Co,
		atom_48Co,
		atom_49Co,
		atom_50Co,
		atom_51Co,
		atom_52Co,
		atom_53Co,
		atom_54Co,
		atom_55Co,
		atom_56Co,
		atom_57Co,
		atom_58Co,
		atom_59Co,
		atom_60Co,
		atom_61Co,
		atom_62Co,
		atom_63Co,
		atom_64Co,
		atom_65Co,
		atom_66Co,
		atom_67Co,
		atom_68Co,
		atom_69Co,
		atom_70Co,
		atom_71Co,
		atom_72Co,
		atom_73Co,
		atom_74Co,
		atom_75Co,
		atom_76Co,
		atom_48Ni,
		atom_49Ni,
		atom_50Ni,
		atom_51Ni,
		atom_52Ni,
		atom_53Ni,
		atom_54Ni,
		atom_55Ni,
		atom_56Ni,
		atom_57Ni,
		atom_58Ni,
		atom_59Ni,
		atom_60Ni,
		atom_61Ni,
		atom_62Ni,
		atom_63Ni,
		atom_64Ni,
		atom_65Ni,
		atom_66Ni,
		atom_67Ni,
		atom_68Ni,
		atom_69Ni,
		atom_70Ni,
		atom_71Ni,
		atom_72Ni,
		atom_73Ni,
		atom_74Ni,
		atom_75Ni,
		atom_76Ni,
		atom_77Ni,
		atom_78Ni,
		atom_79Ni,
		atom_52Cu,
		atom_53Cu,
		atom_54Cu,
		atom_55Cu,
		atom_56Cu,
		atom_57Cu,
		atom_58Cu,
		atom_59Cu,
		atom_60Cu,
		atom_61Cu,
		atom_62Cu,
		atom_63Cu,
		atom_64Cu,
		atom_65Cu,
		atom_66Cu,
		atom_67Cu,
		atom_68Cu,
		atom_69Cu,
		atom_70Cu,
		atom_71Cu,
		atom_72Cu,
		atom_73Cu,
		atom_74Cu,
		atom_75Cu,
		atom_76Cu,
		atom_77Cu,
		atom_78Cu,
		atom_79Cu,
		atom_80Cu,
		atom_81Cu,
		atom_82Cu,
		atom_54Zn,
		atom_55Zn,
		atom_56Zn,
		atom_57Zn,
		atom_58Zn,
		atom_59Zn,
		atom_60Zn,
		atom_61Zn,
		atom_62Zn,
		atom_63Zn,
		atom_64Zn,
		atom_65Zn,
		atom_66Zn,
		atom_67Zn,
		atom_68Zn,
		atom_69Zn,
		atom_70Zn,
		atom_71Zn,
		atom_72Zn,
		atom_73Zn,
		atom_74Zn,
		atom_75Zn,
		atom_76Zn,
		atom_77Zn,
		atom_78Zn,
		atom_79Zn,
		atom_80Zn,
		atom_81Zn,
		atom_82Zn,
		atom_83Zn,
		atom_84Zn,
		atom_85Zn,
		atom_56Ga,
		atom_57Ga,
		atom_58Ga,
		atom_59Ga,
		atom_60Ga,
		atom_61Ga,
		atom_62Ga,
		atom_63Ga,
		atom_64Ga,
		atom_65Ga,
		atom_66Ga,
		atom_67Ga,
		atom_68Ga,
		atom_69Ga,
		atom_70Ga,
		atom_71Ga,
		atom_72Ga,
		atom_73Ga,
		atom_74Ga,
		atom_75Ga,
		atom_76Ga,
		atom_77Ga,
		atom_78Ga,
		atom_79Ga,
		atom_80Ga,
		atom_81Ga,
		atom_82Ga,
		atom_83Ga,
		atom_84Ga,
		atom_85Ga,
		atom_86Ga,
		atom_87Ga,
		atom_58Ge,
		atom_59Ge,
		atom_60Ge,
		atom_61Ge,
		atom_62Ge,
		atom_63Ge,
		atom_64Ge,
		atom_65Ge,
		atom_66Ge,
		atom_67Ge,
		atom_68Ge,
		atom_69Ge,
		atom_70Ge,
		atom_71Ge,
		atom_72Ge,
		atom_73Ge,
		atom_74Ge,
		atom_75Ge,
		atom_76Ge,
		atom_77Ge,
		atom_78Ge,
		atom_79Ge,
		atom_80Ge,
		atom_81Ge,
		atom_82Ge,
		atom_83Ge,
		atom_84Ge,
		atom_85Ge,
		atom_86Ge,
		atom_87Ge,
		atom_88Ge,
		atom_89Ge,
		atom_90Ge,
		atom_60As,
		atom_61As,
		atom_62As,
		atom_63As,
		atom_64As,
		atom_65As,
		atom_66As,
		atom_67As,
		atom_68As,
		atom_69As,
		atom_70As,
		atom_71As,
		atom_72As,
		atom_73As,
		atom_74As,
		atom_75As,
		atom_76As,
		atom_77As,
		atom_78As,
		atom_79As,
		atom_80As,
		atom_81As,
		atom_82As,
		atom_83As,
		atom_84As,
		atom_85As,
		atom_86As,
		atom_87As,
		atom_88As,
		atom_89As,
		atom_90As,
		atom_91As,
		atom_92As,
		atom_64Se,
		atom_65Se,
		atom_66Se,
		atom_67Se,
		atom_68Se,
		atom_69Se,
		atom_70Se,
		atom_71Se,
		atom_72Se,
		atom_73Se,
		atom_74Se,
		atom_75Se,
		atom_76Se,
		atom_77Se,
		atom_78Se,
		atom_79Se,
		atom_80Se,
		atom_81Se,
		atom_82Se,
		atom_83Se,
		atom_84Se,
		atom_85Se,
		atom_86Se,
		atom_87Se,
		atom_88Se,
		atom_89Se,
		atom_90Se,
		atom_91Se,
		atom_92Se,
		atom_93Se,
		atom_94Se,
		atom_95Se,
		atom_67Br,
		atom_68Br,
		atom_69Br,
		atom_70Br,
		atom_71Br,
		atom_72Br,
		atom_73Br,
		atom_74Br,
		atom_75Br,
		atom_76Br,
		atom_77Br,
		atom_78Br,
		atom_79Br,
		atom_80Br,
		atom_81Br,
		atom_82Br,
		atom_83Br,
		atom_84Br,
		atom_85Br,
		atom_86Br,
		atom_87Br,
		atom_88Br,
		atom_89Br,
		atom_90Br,
		atom_91Br,
		atom_92Br,
		atom_93Br,
		atom_94Br,
		atom_95Br,
		atom_96Br,
		atom_97Br,
		atom_98Br,
		atom_69Kr,
		atom_70Kr,
		atom_71Kr,
		atom_72Kr,
		atom_73Kr,
		atom_74Kr,
		atom_75Kr,
		atom_76Kr,
		atom_77Kr,
		atom_78Kr,
		atom_79Kr,
		atom_80Kr,
		atom_81Kr,
		atom_82Kr,
		atom_83Kr,
		atom_84Kr,
		atom_85Kr,
		atom_86Kr,
		atom_87Kr,
		atom_88Kr,
		atom_89Kr,
		atom_90Kr,
		atom_91Kr,
		atom_92Kr,
		atom_93Kr,
		atom_94Kr,
		atom_95Kr,
		atom_96Kr,
		atom_97Kr,
		atom_98Kr,
		atom_99Kr,
		atom_100Kr,
		atom_101Kr,
		atom_71Rb,
		atom_72Rb,
		atom_73Rb,
		atom_74Rb,
		atom_75Rb,
		atom_76Rb,
		atom_77Rb,
		atom_78Rb,
		atom_79Rb,
		atom_80Rb,
		atom_81Rb,
		atom_82Rb,
		atom_83Rb,
		atom_84Rb,
		atom_85Rb,
		atom_86Rb,
		atom_87Rb,
		atom_88Rb,
		atom_89Rb,
		atom_90Rb,
		atom_91Rb,
		atom_92Rb,
		atom_93Rb,
		atom_94Rb,
		atom_95Rb,
		atom_96Rb,
		atom_97Rb,
		atom_98Rb,
		atom_99Rb,
		atom_100Rb,
		atom_101Rb,
		atom_102Rb,
		atom_103Rb,
		atom_73Sr,
		atom_74Sr,
		atom_75Sr,
		atom_76Sr,
		atom_77Sr,
		atom_78Sr,
		atom_79Sr,
		atom_80Sr,
		atom_81Sr,
		atom_82Sr,
		atom_83Sr,
		atom_84Sr,
		atom_85Sr,
		atom_86Sr,
		atom_87Sr,
		atom_88Sr,
		atom_89Sr,
		atom_90Sr,
		atom_91Sr,
		atom_92Sr,
		atom_93Sr,
		atom_94Sr,
		atom_95Sr,
		atom_96Sr,
		atom_97Sr,
		atom_98Sr,
		atom_99Sr,
		atom_100Sr,
		atom_101Sr,
		atom_102Sr,
		atom_103Sr,
		atom_104Sr,
		atom_105Sr,
		atom_106Sr,
		atom_107Sr,
		atom_76Y,
		atom_77Y,
		atom_78Y,
		atom_79Y,
		atom_80Y,
		atom_81Y,
		atom_82Y,
		atom_83Y,
		atom_84Y,
		atom_85Y,
		atom_86Y,
		atom_87Y,
		atom_88Y,
		atom_89Y,
		atom_90Y,
		atom_91Y,
		atom_92Y,
		atom_93Y,
		atom_94Y,
		atom_95Y,
		atom_96Y,
		atom_97Y,
		atom_98Y,
		atom_99Y,
		atom_100Y,
		atom_101Y,
		atom_102Y,
		atom_103Y,
		atom_104Y,
		atom_105Y,
		atom_106Y,
		atom_107Y,
		atom_108Y,
		atom_109Y,
		atom_78Zr,
		atom_79Zr,
		atom_80Zr,
		atom_81Zr,
		atom_82Zr,
		atom_83Zr,
		atom_84Zr,
		atom_85Zr,
		atom_86Zr,
		atom_87Zr,
		atom_88Zr,
		atom_89Zr,
		atom_90Zr,
		atom_91Zr,
		atom_92Zr,
		atom_93Zr,
		atom_94Zr,
		atom_95Zr,
		atom_96Zr,
		atom_97Zr,
		atom_98Zr,
		atom_99Zr,
		atom_100Zr,
		atom_101Zr,
		atom_102Zr,
		atom_103Zr,
		atom_104Zr,
		atom_105Zr,
		atom_106Zr,
		atom_107Zr,
		atom_108Zr,
		atom_109Zr,
		atom_110Zr,
		atom_111Zr,
		atom_112Zr,
		atom_81Nb,
		atom_82Nb,
		atom_83Nb,
		atom_84Nb,
		atom_85Nb,
		atom_86Nb,
		atom_87Nb,
		atom_88Nb,
		atom_89Nb,
		atom_90Nb,
		atom_91Nb,
		atom_92Nb,
		atom_93Nb,
		atom_94Nb,
		atom_95Nb,
		atom_96Nb,
		atom_97Nb,
		atom_98Nb,
		atom_99Nb,
		atom_100Nb,
		atom_101Nb,
		atom_102Nb,
		atom_103Nb,
		atom_104Nb,
		atom_105Nb,
		atom_106Nb,
		atom_107Nb,
		atom_108Nb,
		atom_109Nb,
		atom_110Nb,
		atom_111Nb,
		atom_112Nb,
		atom_113Nb,
		atom_114Nb,
		atom_115Nb,
		atom_83Mo,
		atom_84Mo,
		atom_85Mo,
		atom_86Mo,
		atom_87Mo,
		atom_88Mo,
		atom_89Mo,
		atom_90Mo,
		atom_91Mo,
		atom_92Mo,
		atom_93Mo,
		atom_94Mo,
		atom_95Mo,
		atom_96Mo,
		atom_97Mo,
		atom_98Mo,
		atom_99Mo,
		atom_100Mo,
		atom_101Mo,
		atom_102Mo,
		atom_103Mo,
		atom_104Mo,
		atom_105Mo,
		atom_106Mo,
		atom_107Mo,
		atom_108Mo,
		atom_109Mo,
		atom_110Mo,
		atom_111Mo,
		atom_112Mo,
		atom_113Mo,
		atom_114Mo,
		atom_115Mo,
		atom_116Mo,
		atom_117Mo,
		atom_85Tc,
		atom_86Tc,
		atom_87Tc,
		atom_88Tc,
		atom_89Tc,
		atom_90Tc,
		atom_91Tc,
		atom_92Tc,
		atom_93Tc,
		atom_94Tc,
		atom_95Tc,
		atom_96Tc,
		atom_97Tc,
		atom_98Tc,
		atom_99Tc,
		atom_100Tc,
		atom_101Tc,
		atom_102Tc,
		atom_103Tc,
		atom_104Tc,
		atom_105Tc,
		atom_106Tc,
		atom_107Tc,
		atom_108Tc,
		atom_109Tc,
		atom_110Tc,
		atom_111Tc,
		atom_112Tc,
		atom_113Tc,
		atom_114Tc,
		atom_115Tc,
		atom_116Tc,
		atom_117Tc,
		atom_118Tc,
		atom_119Tc,
		atom_120Tc,
		atom_87Ru,
		atom_88Ru,
		atom_89Ru,
		atom_90Ru,
		atom_91Ru,
		atom_92Ru,
		atom_93Ru,
		atom_94Ru,
		atom_95Ru,
		atom_96Ru,
		atom_97Ru,
		atom_98Ru,
		atom_99Ru,
		atom_100Ru,
		atom_101Ru,
		atom_102Ru,
		atom_103Ru,
		atom_104Ru,
		atom_105Ru,
		atom_106Ru,
		atom_107Ru,
		atom_108Ru,
		atom_109Ru,
		atom_110Ru,
		atom_111Ru,
		atom_112Ru,
		atom_113Ru,
		atom_114Ru,
		atom_115Ru,
		atom_116Ru,
		atom_117Ru,
		atom_118Ru,
		atom_119Ru,
		atom_120Ru,
		atom_121Ru,
		atom_122Ru,
		atom_123Ru,
		atom_124Ru,
		atom_89Rh,
		atom_90Rh,
		atom_91Rh,
		atom_92Rh,
		atom_93Rh,
		atom_94Rh,
		atom_95Rh,
		atom_96Rh,
		atom_97Rh,
		atom_98Rh,
		atom_99Rh,
		atom_100Rh,
		atom_101Rh,
		atom_102Rh,
		atom_103Rh,
		atom_104Rh,
		atom_105Rh,
		atom_106Rh,
		atom_107Rh,
		atom_108Rh,
		atom_109Rh,
		atom_110Rh,
		atom_111Rh,
		atom_112Rh,
		atom_113Rh,
		atom_114Rh,
		atom_115Rh,
		atom_116Rh,
		atom_117Rh,
		atom_118Rh,
		atom_119Rh,
		atom_120Rh,
		atom_121Rh,
		atom_122Rh,
		atom_123Rh,
		atom_124Rh,
		atom_125Rh,
		atom_126Rh,
		atom_91Pd,
		atom_92Pd,
		atom_93Pd,
		atom_94Pd,
		atom_95Pd,
		atom_96Pd,
		atom_97Pd,
		atom_98Pd,
		atom_99Pd,
		atom_100Pd,
		atom_101Pd,
		atom_102Pd,
		atom_103Pd,
		atom_104Pd,
		atom_105Pd,
		atom_106Pd,
		atom_107Pd,
		atom_108Pd,
		atom_109Pd,
		atom_110Pd,
		atom_111Pd,
		atom_112Pd,
		atom_113Pd,
		atom_114Pd,
		atom_115Pd,
		atom_116Pd,
		atom_117Pd,
		atom_118Pd,
		atom_119Pd,
		atom_120Pd,
		atom_121Pd,
		atom_122Pd,
		atom_123Pd,
		atom_124Pd,
		atom_125Pd,
		atom_126Pd,
		atom_127Pd,
		atom_128Pd,
		atom_93Ag,
		atom_94Ag,
		atom_95Ag,
		atom_96Ag,
		atom_97Ag,
		atom_98Ag,
		atom_99Ag,
		atom_100Ag,
		atom_101Ag,
		atom_102Ag,
		atom_103Ag,
		atom_104Ag,
		atom_105Ag,
		atom_106Ag,
		atom_107Ag,
		atom_108Ag,
		atom_109Ag,
		atom_110Ag,
		atom_111Ag,
		atom_112Ag,
		atom_113Ag,
		atom_114Ag,
		atom_115Ag,
		atom_116Ag,
		atom_117Ag,
		atom_118Ag,
		atom_119Ag,
		atom_120Ag,
		atom_121Ag,
		atom_122Ag,
		atom_123Ag,
		atom_124Ag,
		atom_125Ag,
		atom_126Ag,
		atom_127Ag,
		atom_128Ag,
		atom_129Ag,
		atom_130Ag,
		atom_95Cd,
		atom_96Cd,
		atom_97Cd,
		atom_98Cd,
		atom_99Cd,
		atom_100Cd,
		atom_101Cd,
		atom_102Cd,
		atom_103Cd,
		atom_104Cd,
		atom_105Cd,
		atom_106Cd,
		atom_107Cd,
		atom_108Cd,
		atom_109Cd,
		atom_110Cd,
		atom_111Cd,
		atom_112Cd,
		atom_113Cd,
		atom_114Cd,
		atom_115Cd,
		atom_116Cd,
		atom_117Cd,
		atom_118Cd,
		atom_119Cd,
		atom_120Cd,
		atom_121Cd,
		atom_122Cd,
		atom_123Cd,
		atom_124Cd,
		atom_125Cd,
		atom_126Cd,
		atom_127Cd,
		atom_128Cd,
		atom_129Cd,
		atom_130Cd,
		atom_131Cd,
		atom_132Cd,
		atom_133Cd,
		atom_97In,
		atom_98In,
		atom_99In,
		atom_100In,
		atom_101In,
		atom_102In,
		atom_103In,
		atom_104In,
		atom_105In,
		atom_106In,
		atom_107In,
		atom_108In,
		atom_109In,
		atom_110In,
		atom_111In,
		atom_112In,
		atom_113In,
		atom_114In,
		atom_115In,
		atom_116In,
		atom_117In,
		atom_118In,
		atom_119In,
		atom_120In,
		atom_121In,
		atom_122In,
		atom_123In,
		atom_124In,
		atom_125In,
		atom_126In,
		atom_127In,
		atom_128In,
		atom_129In,
		atom_130In,
		atom_131In,
		atom_132In,
		atom_133In,
		atom_134In,
		atom_135In,
		atom_99Sn,
		atom_100Sn,
		atom_101Sn,
		atom_102Sn,
		atom_103Sn,
		atom_104Sn,
		atom_105Sn,
		atom_106Sn,
		atom_107Sn,
		atom_108Sn,
		atom_109Sn,
		atom_110Sn,
		atom_111Sn,
		atom_112Sn,
		atom_113Sn,
		atom_114Sn,
		atom_115Sn,
		atom_116Sn,
		atom_117Sn,
		atom_118Sn,
		atom_119Sn,
		atom_120Sn,
		atom_121Sn,
		atom_122Sn,
		atom_123Sn,
		atom_124Sn,
		atom_125Sn,
		atom_126Sn,
		atom_127Sn,
		atom_128Sn,
		atom_129Sn,
		atom_130Sn,
		atom_131Sn,
		atom_132Sn,
		atom_133Sn,
		atom_134Sn,
		atom_135Sn,
		atom_136Sn,
		atom_137Sn,
		atom_138Sn,
		atom_103Sb,
		atom_104Sb,
		atom_105Sb,
		atom_106Sb,
		atom_107Sb,
		atom_108Sb,
		atom_109Sb,
		atom_110Sb,
		atom_111Sb,
		atom_112Sb,
		atom_113Sb,
		atom_114Sb,
		atom_115Sb,
		atom_116Sb,
		atom_117Sb,
		atom_118Sb,
		atom_119Sb,
		atom_120Sb,
		atom_121Sb,
		atom_122Sb,
		atom_123Sb,
		atom_124Sb,
		atom_125Sb,
		atom_126Sb,
		atom_127Sb,
		atom_128Sb,
		atom_129Sb,
		atom_130Sb,
		atom_131Sb,
		atom_132Sb,
		atom_133Sb,
		atom_134Sb,
		atom_135Sb,
		atom_136Sb,
		atom_137Sb,
		atom_138Sb,
		atom_139Sb,
		atom_140Sb,
		atom_105Te,
		atom_106Te,
		atom_107Te,
		atom_108Te,
		atom_109Te,
		atom_110Te,
		atom_111Te,
		atom_112Te,
		atom_113Te,
		atom_114Te,
		atom_115Te,
		atom_116Te,
		atom_117Te,
		atom_118Te,
		atom_119Te,
		atom_120Te,
		atom_121Te,
		atom_122Te,
		atom_123Te,
		atom_124Te,
		atom_125Te,
		atom_126Te,
		atom_127Te,
		atom_128Te,
		atom_129Te,
		atom_130Te,
		atom_131Te,
		atom_132Te,
		atom_133Te,
		atom_134Te,
		atom_135Te,
		atom_136Te,
		atom_137Te,
		atom_138Te,
		atom_139Te,
		atom_140Te,
		atom_141Te,
		atom_142Te,
		atom_143Te,
		atom_107I,
		atom_108I,
		atom_109I,
		atom_110I,
		atom_111I,
		atom_112I,
		atom_113I,
		atom_114I,
		atom_115I,
		atom_116I,
		atom_117I,
		atom_118I,
		atom_119I,
		atom_120I,
		atom_121I,
		atom_122I,
		atom_123I,
		atom_124I,
		atom_125I,
		atom_126I,
		atom_127I,
		atom_128I,
		atom_129I,
		atom_130I,
		atom_131I,
		atom_132I,
		atom_133I,
		atom_134I,
		atom_135I,
		atom_136I,
		atom_137I,
		atom_138I,
		atom_139I,
		atom_140I,
		atom_141I,
		atom_142I,
		atom_143I,
		atom_144I,
		atom_145I,
		atom_109Xe,
		atom_110Xe,
		atom_111Xe,
		atom_112Xe,
		atom_113Xe,
		atom_114Xe,
		atom_115Xe,
		atom_116Xe,
		atom_117Xe,
		atom_118Xe,
		atom_119Xe,
		atom_120Xe,
		atom_121Xe,
		atom_122Xe,
		atom_123Xe,
		atom_124Xe,
		atom_125Xe,
		atom_126Xe,
		atom_127Xe,
		atom_128Xe,
		atom_129Xe,
		atom_130Xe,
		atom_131Xe,
		atom_132Xe,
		atom_133Xe,
		atom_134Xe,
		atom_135Xe,
		atom_136Xe,
		atom_137Xe,
		atom_138Xe,
		atom_139Xe,
		atom_140Xe,
		atom_141Xe,
		atom_142Xe,
		atom_143Xe,
		atom_144Xe,
		atom_145Xe,
		atom_146Xe,
		atom_147Xe,
		atom_148Xe,
		atom_112Cs,
		atom_113Cs,
		atom_114Cs,
		atom_115Cs,
		atom_116Cs,
		atom_117Cs,
		atom_118Cs,
		atom_119Cs,
		atom_120Cs,
		atom_121Cs,
		atom_122Cs,
		atom_123Cs,
		atom_124Cs,
		atom_125Cs,
		atom_126Cs,
		atom_127Cs,
		atom_128Cs,
		atom_129Cs,
		atom_130Cs,
		atom_131Cs,
		atom_132Cs,
		atom_133Cs,
		atom_134Cs,
		atom_135Cs,
		atom_136Cs,
		atom_137Cs,
		atom_138Cs,
		atom_139Cs,
		atom_140Cs,
		atom_141Cs,
		atom_142Cs,
		atom_143Cs,
		atom_144Cs,
		atom_145Cs,
		atom_146Cs,
		atom_147Cs,
		atom_148Cs,
		atom_149Cs,
		atom_150Cs,
		atom_151Cs,
		atom_114Ba,
		atom_115Ba,
		atom_116Ba,
		atom_117Ba,
		atom_118Ba,
		atom_119Ba,
		atom_120Ba,
		atom_121Ba,
		atom_122Ba,
		atom_123Ba,
		atom_124Ba,
		atom_125Ba,
		atom_126Ba,
		atom_127Ba,
		atom_128Ba,
		atom_129Ba,
		atom_130Ba,
		atom_131Ba,
		atom_132Ba,
		atom_133Ba,
		atom_134Ba,
		atom_135Ba,
		atom_136Ba,
		atom_137Ba,
		atom_138Ba,
		atom_139Ba,
		atom_140Ba,
		atom_141Ba,
		atom_142Ba,
		atom_143Ba,
		atom_144Ba,
		atom_145Ba,
		atom_146Ba,
		atom_147Ba,
		atom_148Ba,
		atom_149Ba,
		atom_150Ba,
		atom_151Ba,
		atom_152Ba,
		atom_153Ba,
		atom_116La,
		atom_117La,
		atom_118La,
		atom_119La,
		atom_120La,
		atom_121La,
		atom_122La,
		atom_123La,
		atom_124La,
		atom_125La,
		atom_126La,
		atom_127La,
		atom_128La,
		atom_129La,
		atom_130La,
		atom_131La,
		atom_132La,
		atom_133La,
		atom_134La,
		atom_135La,
		atom_136La,
		atom_137La,
		atom_138La,
		atom_139La,
		atom_140La,
		atom_141La,
		atom_142La,
		atom_143La,
		atom_144La,
		atom_145La,
		atom_146La,
		atom_147La,
		atom_148La,
		atom_149La,
		atom_150La,
		atom_151La,
		atom_152La,
		atom_153La,
		atom_154La,
		atom_155La,
		atom_119Ce,
		atom_120Ce,
		atom_121Ce,
		atom_122Ce,
		atom_123Ce,
		atom_124Ce,
		atom_125Ce,
		atom_126Ce,
		atom_127Ce,
		atom_128Ce,
		atom_129Ce,
		atom_130Ce,
		atom_131Ce,
		atom_132Ce,
		atom_133Ce,
		atom_134Ce,
		atom_135Ce,
		atom_136Ce,
		atom_137Ce,
		atom_138Ce,
		atom_139Ce,
		atom_140Ce,
		atom_141Ce,
		atom_142Ce,
		atom_143Ce,
		atom_144Ce,
		atom_145Ce,
		atom_146Ce,
		atom_147Ce,
		atom_148Ce,
		atom_149Ce,
		atom_150Ce,
		atom_151Ce,
		atom_152Ce,
		atom_153Ce,
		atom_154Ce,
		atom_155Ce,
		atom_156Ce,
		atom_157Ce,
		atom_121Pr,
		atom_122Pr,
		atom_123Pr,
		atom_124Pr,
		atom_125Pr,
		atom_126Pr,
		atom_127Pr,
		atom_128Pr,
		atom_129Pr,
		atom_130Pr,
		atom_131Pr,
		atom_132Pr,
		atom_133Pr,
		atom_134Pr,
		atom_135Pr,
		atom_136Pr,
		atom_137Pr,
		atom_138Pr,
		atom_139Pr,
		atom_140Pr,
		atom_141Pr,
		atom_142Pr,
		atom_143Pr,
		atom_144Pr,
		atom_145Pr,
		atom_146Pr,
		atom_147Pr,
		atom_148Pr,
		atom_149Pr,
		atom_150Pr,
		atom_151Pr,
		atom_152Pr,
		atom_153Pr,
		atom_154Pr,
		atom_155Pr,
		atom_156Pr,
		atom_157Pr,
		atom_158Pr,
		atom_159Pr,
		atom_124Nd,
		atom_125Nd,
		atom_126Nd,
		atom_127Nd,
		atom_128Nd,
		atom_129Nd,
		atom_130Nd,
		atom_131Nd,
		atom_132Nd,
		atom_133Nd,
		atom_134Nd,
		atom_135Nd,
		atom_136Nd,
		atom_137Nd,
		atom_138Nd,
		atom_139Nd,
		atom_140Nd,
		atom_141Nd,
		atom_142Nd,
		atom_143Nd,
		atom_144Nd,
		atom_145Nd,
		atom_146Nd,
		atom_147Nd,
		atom_148Nd,
		atom_149Nd,
		atom_150Nd,
		atom_151Nd,
		atom_152Nd,
		atom_153Nd,
		atom_154Nd,
		atom_155Nd,
		atom_156Nd,
		atom_157Nd,
		atom_158Nd,
		atom_159Nd,
		atom_160Nd,
		atom_161Nd,
		atom_126Pm,
		atom_127Pm,
		atom_128Pm,
		atom_129Pm,
		atom_130Pm,
		atom_131Pm,
		atom_132Pm,
		atom_133Pm,
		atom_134Pm,
		atom_135Pm,
		atom_136Pm,
		atom_137Pm,
		atom_138Pm,
		atom_139Pm,
		atom_140Pm,
		atom_141Pm,
		atom_142Pm,
		atom_143Pm,
		atom_144Pm,
		atom_145Pm,
		atom_146Pm,
		atom_147Pm,
		atom_148Pm,
		atom_149Pm,
		atom_150Pm,
		atom_151Pm,
		atom_152Pm,
		atom_153Pm,
		atom_154Pm,
		atom_155Pm,
		atom_156Pm,
		atom_157Pm,
		atom_158Pm,
		atom_159Pm,
		atom_160Pm,
		atom_161Pm,
		atom_162Pm,
		atom_163Pm,
		atom_128Sm,
		atom_129Sm,
		atom_130Sm,
		atom_131Sm,
		atom_132Sm,
		atom_133Sm,
		atom_134Sm,
		atom_135Sm,
		atom_136Sm,
		atom_137Sm,
		atom_138Sm,
		atom_139Sm,
		atom_140Sm,
		atom_141Sm,
		atom_142Sm,
		atom_143Sm,
		atom_144Sm,
		atom_145Sm,
		atom_146Sm,
		atom_147Sm,
		atom_148Sm,
		atom_149Sm,
		atom_150Sm,
		atom_151Sm,
		atom_152Sm,
		atom_153Sm,
		atom_154Sm,
		atom_155Sm,
		atom_156Sm,
		atom_157Sm,
		atom_158Sm,
		atom_159Sm,
		atom_160Sm,
		atom_161Sm,
		atom_162Sm,
		atom_163Sm,
		atom_164Sm,
		atom_165Sm,
		atom_130Eu,
		atom_131Eu,
		atom_132Eu,
		atom_133Eu,
		atom_134Eu,
		atom_135Eu,
		atom_136Eu,
		atom_137Eu,
		atom_138Eu,
		atom_139Eu,
		atom_140Eu,
		atom_141Eu,
		atom_142Eu,
		atom_143Eu,
		atom_144Eu,
		atom_145Eu,
		atom_146Eu,
		atom_147Eu,
		atom_148Eu,
		atom_149Eu,
		atom_150Eu,
		atom_151Eu,
		atom_152Eu,
		atom_153Eu,
		atom_154Eu,
		atom_155Eu,
		atom_156Eu,
		atom_157Eu,
		atom_158Eu,
		atom_159Eu,
		atom_160Eu,
		atom_161Eu,
		atom_162Eu,
		atom_163Eu,
		atom_164Eu,
		atom_165Eu,
		atom_166Eu,
		atom_167Eu,
		atom_133Gd,
		atom_134Gd,
		atom_135Gd,
		atom_136Gd,
		atom_137Gd,
		atom_138Gd,
		atom_139Gd,
		atom_140Gd,
		atom_141Gd,
		atom_142Gd,
		atom_143Gd,
		atom_144Gd,
		atom_145Gd,
		atom_146Gd,
		atom_147Gd,
		atom_148Gd,
		atom_149Gd,
		atom_150Gd,
		atom_151Gd,
		atom_152Gd,
		atom_153Gd,
		atom_154Gd,
		atom_155Gd,
		atom_156Gd,
		atom_157Gd,
		atom_158Gd,
		atom_159Gd,
		atom_160Gd,
		atom_161Gd,
		atom_162Gd,
		atom_163Gd,
		atom_164Gd,
		atom_165Gd,
		atom_166Gd,
		atom_167Gd,
		atom_168Gd,
		atom_169Gd,
		atom_135Tb,
		atom_136Tb,
		atom_137Tb,
		atom_138Tb,
		atom_139Tb,
		atom_140Tb,
		atom_141Tb,
		atom_142Tb,
		atom_143Tb,
		atom_144Tb,
		atom_145Tb,
		atom_146Tb,
		atom_147Tb,
		atom_148Tb,
		atom_149Tb,
		atom_150Tb,
		atom_151Tb,
		atom_152Tb,
		atom_153Tb,
		atom_154Tb,
		atom_155Tb,
		atom_156Tb,
		atom_157Tb,
		atom_158Tb,
		atom_159Tb,
		atom_160Tb,
		atom_161Tb,
		atom_162Tb,
		atom_163Tb,
		atom_164Tb,
		atom_165Tb,
		atom_166Tb,
		atom_167Tb,
		atom_168Tb,
		atom_169Tb,
		atom_170Tb,
		atom_171Tb,
		atom_138Dy,
		atom_139Dy,
		atom_140Dy,
		atom_141Dy,
		atom_142Dy,
		atom_143Dy,
		atom_144Dy,
		atom_145Dy,
		atom_146Dy,
		atom_147Dy,
		atom_148Dy,
		atom_149Dy,
		atom_150Dy,
		atom_151Dy,
		atom_152Dy,
		atom_153Dy,
		atom_154Dy,
		atom_155Dy,
		atom_156Dy,
		atom_157Dy,
		atom_158Dy,
		atom_159Dy,
		atom_160Dy,
		atom_161Dy,
		atom_162Dy,
		atom_163Dy,
		atom_164Dy,
		atom_165Dy,
		atom_166Dy,
		atom_167Dy,
		atom_168Dy,
		atom_169Dy,
		atom_170Dy,
		atom_171Dy,
		atom_172Dy,
		atom_173Dy,
		atom_140Ho,
		atom_141Ho,
		atom_142Ho,
		atom_143Ho,
		atom_144Ho,
		atom_145Ho,
		atom_146Ho,
		atom_147Ho,
		atom_148Ho,
		atom_149Ho,
		atom_150Ho,
		atom_151Ho,
		atom_152Ho,
		atom_153Ho,
		atom_154Ho,
		atom_155Ho,
		atom_156Ho,
		atom_157Ho,
		atom_158Ho,
		atom_159Ho,
		atom_160Ho,
		atom_161Ho,
		atom_162Ho,
		atom_163Ho,
		atom_164Ho,
		atom_165Ho,
		atom_166Ho,
		atom_167Ho,
		atom_168Ho,
		atom_169Ho,
		atom_170Ho,
		atom_171Ho,
		atom_172Ho,
		atom_173Ho,
		atom_174Ho,
		atom_175Ho,
		atom_142Er,
		atom_143Er,
		atom_144Er,
		atom_145Er,
		atom_146Er,
		atom_147Er,
		atom_148Er,
		atom_149Er,
		atom_150Er,
		atom_151Er,
		atom_152Er,
		atom_153Er,
		atom_154Er,
		atom_155Er,
		atom_156Er,
		atom_157Er,
		atom_158Er,
		atom_159Er,
		atom_160Er,
		atom_161Er,
		atom_162Er,
		atom_163Er,
		atom_164Er,
		atom_165Er,
		atom_166Er,
		atom_167Er,
		atom_168Er,
		atom_169Er,
		atom_170Er,
		atom_171Er,
		atom_172Er,
		atom_173Er,
		atom_174Er,
		atom_175Er,
		atom_176Er,
		atom_177Er,
		atom_144Tm,
		atom_145Tm,
		atom_146Tm,
		atom_147Tm,
		atom_148Tm,
		atom_149Tm,
		atom_150Tm,
		atom_151Tm,
		atom_152Tm,
		atom_153Tm,
		atom_154Tm,
		atom_155Tm,
		atom_156Tm,
		atom_157Tm,
		atom_158Tm,
		atom_159Tm,
		atom_160Tm,
		atom_161Tm,
		atom_162Tm,
		atom_163Tm,
		atom_164Tm,
		atom_165Tm,
		atom_166Tm,
		atom_167Tm,
		atom_168Tm,
		atom_169Tm,
		atom_170Tm,
		atom_171Tm,
		atom_172Tm,
		atom_173Tm,
		atom_174Tm,
		atom_175Tm,
		atom_176Tm,
		atom_177Tm,
		atom_178Tm,
		atom_179Tm,
		atom_148Yb,
		atom_149Yb,
		atom_150Yb,
		atom_151Yb,
		atom_152Yb,
		atom_153Yb,
		atom_154Yb,
		atom_155Yb,
		atom_156Yb,
		atom_157Yb,
		atom_158Yb,
		atom_159Yb,
		atom_160Yb,
		atom_161Yb,
		atom_162Yb,
		atom_163Yb,
		atom_164Yb,
		atom_165Yb,
		atom_166Yb,
		atom_167Yb,
		atom_168Yb,
		atom_169Yb,
		atom_170Yb,
		atom_171Yb,
		atom_172Yb,
		atom_173Yb,
		atom_174Yb,
		atom_175Yb,
		atom_176Yb,
		atom_177Yb,
		atom_178Yb,
		atom_179Yb,
		atom_180Yb,
		atom_181Yb,
		atom_150Lu,
		atom_151Lu,
		atom_152Lu,
		atom_153Lu,
		atom_154Lu,
		atom_155Lu,
		atom_156Lu,
		atom_157Lu,
		atom_158Lu,
		atom_159Lu,
		atom_160Lu,
		atom_161Lu,
		atom_162Lu,
		atom_163Lu,
		atom_164Lu,
		atom_165Lu,
		atom_166Lu,
		atom_167Lu,
		atom_168Lu,
		atom_169Lu,
		atom_170Lu,
		atom_171Lu,
		atom_172Lu,
		atom_173Lu,
		atom_174Lu,
		atom_175Lu,
		atom_176Lu,
		atom_177Lu,
		atom_178Lu,
		atom_179Lu,
		atom_180Lu,
		atom_181Lu,
		atom_182Lu,
		atom_183Lu,
		atom_184Lu,
		atom_185Lu,
		atom_153Hf,
		atom_154Hf,
		atom_155Hf,
		atom_156Hf,
		atom_157Hf,
		atom_158Hf,
		atom_159Hf,
		atom_160Hf,
		atom_161Hf,
		atom_162Hf,
		atom_163Hf,
		atom_164Hf,
		atom_165Hf,
		atom_166Hf,
		atom_167Hf,
		atom_168Hf,
		atom_169Hf,
		atom_170Hf,
		atom_171Hf,
		atom_172Hf,
		atom_173Hf,
		atom_174Hf,
		atom_175Hf,
		atom_176Hf,
		atom_177Hf,
		atom_178Hf,
		atom_179Hf,
		atom_180Hf,
		atom_181Hf,
		atom_182Hf,
		atom_183Hf,
		atom_184Hf,
		atom_185Hf,
		atom_186Hf,
		atom_187Hf,
		atom_188Hf,
		atom_189Hf,
		atom_155Ta,
		atom_156Ta,
		atom_157Ta,
		atom_158Ta,
		atom_159Ta,
		atom_160Ta,
		atom_161Ta,
		atom_162Ta,
		atom_163Ta,
		atom_164Ta,
		atom_165Ta,
		atom_166Ta,
		atom_167Ta,
		atom_168Ta,
		atom_169Ta,
		atom_170Ta,
		atom_171Ta,
		atom_172Ta,
		atom_173Ta,
		atom_174Ta,
		atom_175Ta,
		atom_176Ta,
		atom_177Ta,
		atom_178Ta,
		atom_179Ta,
		atom_180Ta,
		atom_181Ta,
		atom_182Ta,
		atom_183Ta,
		atom_184Ta,
		atom_185Ta,
		atom_186Ta,
		atom_187Ta,
		atom_188Ta,
		atom_189Ta,
		atom_190Ta,
		atom_191Ta,
		atom_192Ta,
		atom_157W,
		atom_158W,
		atom_159W,
		atom_160W,
		atom_161W,
		atom_162W,
		atom_163W,
		atom_164W,
		atom_165W,
		atom_166W,
		atom_167W,
		atom_168W,
		atom_169W,
		atom_170W,
		atom_171W,
		atom_172W,
		atom_173W,
		atom_174W,
		atom_175W,
		atom_176W,
		atom_177W,
		atom_178W,
		atom_179W,
		atom_180W,
		atom_181W,
		atom_182W,
		atom_183W,
		atom_184W,
		atom_185W,
		atom_186W,
		atom_187W,
		atom_188W,
		atom_189W,
		atom_190W,
		atom_191W,
		atom_192W,
		atom_193W,
		atom_194W,
		atom_159Re,
		atom_160Re,
		atom_161Re,
		atom_162Re,
		atom_163Re,
		atom_164Re,
		atom_165Re,
		atom_166Re,
		atom_167Re,
		atom_168Re,
		atom_169Re,
		atom_170Re,
		atom_171Re,
		atom_172Re,
		atom_173Re,
		atom_174Re,
		atom_175Re,
		atom_176Re,
		atom_177Re,
		atom_178Re,
		atom_179Re,
		atom_180Re,
		atom_181Re,
		atom_182Re,
		atom_183Re,
		atom_184Re,
		atom_185Re,
		atom_186Re,
		atom_187Re,
		atom_188Re,
		atom_189Re,
		atom_190Re,
		atom_191Re,
		atom_192Re,
		atom_193Re,
		atom_194Re,
		atom_195Re,
		atom_196Re,
		atom_197Re,
		atom_198Re,
		atom_161Os,
		atom_162Os,
		atom_163Os,
		atom_164Os,
		atom_165Os,
		atom_166Os,
		atom_167Os,
		atom_168Os,
		atom_169Os,
		atom_170Os,
		atom_171Os,
		atom_172Os,
		atom_173Os,
		atom_174Os,
		atom_175Os,
		atom_176Os,
		atom_177Os,
		atom_178Os,
		atom_179Os,
		atom_180Os,
		atom_181Os,
		atom_182Os,
		atom_183Os,
		atom_184Os,
		atom_185Os,
		atom_186Os,
		atom_187Os,
		atom_188Os,
		atom_189Os,
		atom_190Os,
		atom_191Os,
		atom_192Os,
		atom_193Os,
		atom_194Os,
		atom_195Os,
		atom_196Os,
		atom_197Os,
		atom_198Os,
		atom_199Os,
		atom_200Os,
		atom_201Os,
		atom_202Os,
		atom_164Ir,
		atom_165Ir,
		atom_166Ir,
		atom_167Ir,
		atom_168Ir,
		atom_169Ir,
		atom_170Ir,
		atom_171Ir,
		atom_172Ir,
		atom_173Ir,
		atom_174Ir,
		atom_175Ir,
		atom_176Ir,
		atom_177Ir,
		atom_178Ir,
		atom_179Ir,
		atom_180Ir,
		atom_181Ir,
		atom_182Ir,
		atom_183Ir,
		atom_184Ir,
		atom_185Ir,
		atom_186Ir,
		atom_187Ir,
		atom_188Ir,
		atom_189Ir,
		atom_190Ir,
		atom_191Ir,
		atom_192Ir,
		atom_193Ir,
		atom_194Ir,
		atom_195Ir,
		atom_196Ir,
		atom_197Ir,
		atom_198Ir,
		atom_199Ir,
		atom_200Ir,
		atom_201Ir,
		atom_202Ir,
		atom_203Ir,
		atom_204Ir,
		atom_166Pt,
		atom_167Pt,
		atom_168Pt,
		atom_169Pt,
		atom_170Pt,
		atom_171Pt,
		atom_172Pt,
		atom_173Pt,
		atom_174Pt,
		atom_175Pt,
		atom_176Pt,
		atom_177Pt,
		atom_178Pt,
		atom_179Pt,
		atom_180Pt,
		atom_181Pt,
		atom_182Pt,
		atom_183Pt,
		atom_184Pt,
		atom_185Pt,
		atom_186Pt,
		atom_187Pt,
		atom_188Pt,
		atom_189Pt,
		atom_190Pt,
		atom_191Pt,
		atom_192Pt,
		atom_193Pt,
		atom_194Pt,
		atom_195Pt,
		atom_196Pt,
		atom_197Pt,
		atom_198Pt,
		atom_199Pt,
		atom_200Pt,
		atom_201Pt,
		atom_202Pt,
		atom_203Pt,
		atom_204Pt,
		atom_205Pt,
		atom_206Pt,
		atom_169Au,
		atom_170Au,
		atom_171Au,
		atom_172Au,
		atom_173Au,
		atom_174Au,
		atom_175Au,
		atom_176Au,
		atom_177Au,
		atom_178Au,
		atom_179Au,
		atom_180Au,
		atom_181Au,
		atom_182Au,
		atom_183Au,
		atom_184Au,
		atom_185Au,
		atom_186Au,
		atom_187Au,
		atom_188Au,
		atom_189Au,
		atom_190Au,
		atom_191Au,
		atom_192Au,
		atom_193Au,
		atom_194Au,
		atom_195Au,
		atom_196Au,
		atom_197Au,
		atom_198Au,
		atom_199Au,
		atom_200Au,
		atom_201Au,
		atom_202Au,
		atom_203Au,
		atom_204Au,
		atom_205Au,
		atom_206Au,
		atom_207Au,
		atom_208Au,
		atom_209Au,
		atom_210Au,
		atom_171Hg,
		atom_172Hg,
		atom_173Hg,
		atom_174Hg,
		atom_175Hg,
		atom_176Hg,
		atom_177Hg,
		atom_178Hg,
		atom_179Hg,
		atom_180Hg,
		atom_181Hg,
		atom_182Hg,
		atom_183Hg,
		atom_184Hg,
		atom_185Hg,
		atom_186Hg,
		atom_187Hg,
		atom_188Hg,
		atom_189Hg,
		atom_190Hg,
		atom_191Hg,
		atom_192Hg,
		atom_193Hg,
		atom_194Hg,
		atom_195Hg,
		atom_196Hg,
		atom_197Hg,
		atom_198Hg,
		atom_199Hg,
		atom_200Hg,
		atom_201Hg,
		atom_202Hg,
		atom_203Hg,
		atom_204Hg,
		atom_205Hg,
		atom_206Hg,
		atom_207Hg,
		atom_208Hg,
		atom_209Hg,
		atom_210Hg,
		atom_211Hg,
		atom_212Hg,
		atom_213Hg,
		atom_214Hg,
		atom_215Hg,
		atom_216Hg,
		atom_176Tl,
		atom_177Tl,
		atom_178Tl,
		atom_179Tl,
		atom_180Tl,
		atom_181Tl,
		atom_182Tl,
		atom_183Tl,
		atom_184Tl,
		atom_185Tl,
		atom_186Tl,
		atom_187Tl,
		atom_188Tl,
		atom_189Tl,
		atom_190Tl,
		atom_191Tl,
		atom_192Tl,
		atom_193Tl,
		atom_194Tl,
		atom_195Tl,
		atom_196Tl,
		atom_197Tl,
		atom_198Tl,
		atom_199Tl,
		atom_200Tl,
		atom_201Tl,
		atom_202Tl,
		atom_203Tl,
		atom_204Tl,
		atom_205Tl,
		atom_206Tl,
		atom_207Tl,
		atom_208Tl,
		atom_209Tl,
		atom_210Tl,
		atom_211Tl,
		atom_212Tl,
		atom_213Tl,
		atom_214Tl,
		atom_215Tl,
		atom_216Tl,
		atom_217Tl,
		atom_218Tl,
		atom_178Pb,
		atom_179Pb,
		atom_180Pb,
		atom_181Pb,
		atom_182Pb,
		atom_183Pb,
		atom_184Pb,
		atom_185Pb,
		atom_186Pb,
		atom_187Pb,
		atom_188Pb,
		atom_189Pb,
		atom_190Pb,
		atom_191Pb,
		atom_192Pb,
		atom_193Pb,
		atom_194Pb,
		atom_195Pb,
		atom_196Pb,
		atom_197Pb,
		atom_198Pb,
		atom_199Pb,
		atom_200Pb,
		atom_201Pb,
		atom_202Pb,
		atom_203Pb,
		atom_204Pb,
		atom_205Pb,
		atom_206Pb,
		atom_207Pb,
		atom_208Pb,
		atom_209Pb,
		atom_210Pb,
		atom_211Pb,
		atom_212Pb,
		atom_213Pb,
		atom_214Pb,
		atom_215Pb,
		atom_216Pb,
		atom_217Pb,
		atom_218Pb,
		atom_219Pb,
		atom_220Pb,
		atom_184Bi,
		atom_185Bi,
		atom_186Bi,
		atom_187Bi,
		atom_188Bi,
		atom_189Bi,
		atom_190Bi,
		atom_191Bi,
		atom_192Bi,
		atom_193Bi,
		atom_194Bi,
		atom_195Bi,
		atom_196Bi,
		atom_197Bi,
		atom_198Bi,
		atom_199Bi,
		atom_200Bi,
		atom_201Bi,
		atom_202Bi,
		atom_203Bi,
		atom_204Bi,
		atom_205Bi,
		atom_206Bi,
		atom_207Bi,
		atom_208Bi,
		atom_209Bi,
		atom_210Bi,
		atom_211Bi,
		atom_212Bi,
		atom_213Bi,
		atom_214Bi,
		atom_215Bi,
		atom_216Bi,
		atom_217Bi,
		atom_218Bi,
		atom_219Bi,
		atom_220Bi,
		atom_221Bi,
		atom_222Bi,
		atom_223Bi,
		atom_224Bi,
		atom_186Po,
		atom_187Po,
		atom_188Po,
		atom_189Po,
		atom_190Po,
		atom_191Po,
		atom_192Po,
		atom_193Po,
		atom_194Po,
		atom_195Po,
		atom_196Po,
		atom_197Po,
		atom_198Po,
		atom_199Po,
		atom_200Po,
		atom_201Po,
		atom_202Po,
		atom_203Po,
		atom_204Po,
		atom_205Po,
		atom_206Po,
		atom_207Po,
		atom_208Po,
		atom_209Po,
		atom_210Po,
		atom_211Po,
		atom_212Po,
		atom_213Po,
		atom_214Po,
		atom_215Po,
		atom_216Po,
		atom_217Po,
		atom_218Po,
		atom_219Po,
		atom_220Po,
		atom_221Po,
		atom_222Po,
		atom_223Po,
		atom_224Po,
		atom_225Po,
		atom_226Po,
		atom_227Po,
		atom_191At,
		atom_192At,
		atom_193At,
		atom_194At,
		atom_195At,
		atom_196At,
		atom_197At,
		atom_198At,
		atom_199At,
		atom_200At,
		atom_201At,
		atom_202At,
		atom_203At,
		atom_204At,
		atom_205At,
		atom_206At,
		atom_207At,
		atom_208At,
		atom_209At,
		atom_210At,
		atom_211At,
		atom_212At,
		atom_213At,
		atom_214At,
		atom_215At,
		atom_216At,
		atom_217At,
		atom_218At,
		atom_219At,
		atom_220At,
		atom_221At,
		atom_222At,
		atom_223At,
		atom_224At,
		atom_225At,
		atom_226At,
		atom_227At,
		atom_228At,
		atom_229At,
		atom_193Rn,
		atom_194Rn,
		atom_195Rn,
		atom_196Rn,
		atom_197Rn,
		atom_198Rn,
		atom_199Rn,
		atom_200Rn,
		atom_201Rn,
		atom_202Rn,
		atom_203Rn,
		atom_204Rn,
		atom_205Rn,
		atom_206Rn,
		atom_207Rn,
		atom_208Rn,
		atom_209Rn,
		atom_210Rn,
		atom_211Rn,
		atom_212Rn,
		atom_213Rn,
		atom_214Rn,
		atom_215Rn,
		atom_216Rn,
		atom_217Rn,
		atom_218Rn,
		atom_219Rn,
		atom_220Rn,
		atom_221Rn,
		atom_222Rn,
		atom_223Rn,
		atom_224Rn,
		atom_225Rn,
		atom_226Rn,
		atom_227Rn,
		atom_228Rn,
		atom_229Rn,
		atom_230Rn,
		atom_231Rn,
		atom_199Fr,
		atom_200Fr,
		atom_201Fr,
		atom_202Fr,
		atom_203Fr,
		atom_204Fr,
		atom_205Fr,
		atom_206Fr,
		atom_207Fr,
		atom_208Fr,
		atom_209Fr,
		atom_210Fr,
		atom_211Fr,
		atom_212Fr,
		atom_213Fr,
		atom_214Fr,
		atom_215Fr,
		atom_216Fr,
		atom_217Fr,
		atom_218Fr,
		atom_219Fr,
		atom_220Fr,
		atom_221Fr,
		atom_222Fr,
		atom_223Fr,
		atom_224Fr,
		atom_225Fr,
		atom_226Fr,
		atom_227Fr,
		atom_228Fr,
		atom_229Fr,
		atom_230Fr,
		atom_231Fr,
		atom_232Fr,
		atom_233Fr,
		atom_201Ra,
		atom_202Ra,
		atom_203Ra,
		atom_204Ra,
		atom_205Ra,
		atom_206Ra,
		atom_207Ra,
		atom_208Ra,
		atom_209Ra,
		atom_210Ra,
		atom_211Ra,
		atom_212Ra,
		atom_213Ra,
		atom_214Ra,
		atom_215Ra,
		atom_216Ra,
		atom_217Ra,
		atom_218Ra,
		atom_219Ra,
		atom_220Ra,
		atom_221Ra,
		atom_222Ra,
		atom_223Ra,
		atom_224Ra,
		atom_225Ra,
		atom_226Ra,
		atom_227Ra,
		atom_228Ra,
		atom_229Ra,
		atom_230Ra,
		atom_231Ra,
		atom_232Ra,
		atom_233Ra,
		atom_234Ra,
		atom_235Ra,
		atom_206Ac,
		atom_207Ac,
		atom_208Ac,
		atom_209Ac,
		atom_210Ac,
		atom_211Ac,
		atom_212Ac,
		atom_213Ac,
		atom_214Ac,
		atom_215Ac,
		atom_216Ac,
		atom_217Ac,
		atom_218Ac,
		atom_219Ac,
		atom_220Ac,
		atom_221Ac,
		atom_222Ac,
		atom_223Ac,
		atom_224Ac,
		atom_225Ac,
		atom_226Ac,
		atom_227Ac,
		atom_228Ac,
		atom_229Ac,
		atom_230Ac,
		atom_231Ac,
		atom_232Ac,
		atom_233Ac,
		atom_234Ac,
		atom_235Ac,
		atom_236Ac,
		atom_237Ac,
		atom_208Th,
		atom_209Th,
		atom_210Th,
		atom_211Th,
		atom_212Th,
		atom_213Th,
		atom_214Th,
		atom_215Th,
		atom_216Th,
		atom_217Th,
		atom_218Th,
		atom_219Th,
		atom_220Th,
		atom_221Th,
		atom_222Th,
		atom_223Th,
		atom_224Th,
		atom_225Th,
		atom_226Th,
		atom_227Th,
		atom_228Th,
		atom_229Th,
		atom_230Th,
		atom_231Th,
		atom_232Th,
		atom_233Th,
		atom_234Th,
		atom_235Th,
		atom_236Th,
		atom_237Th,
		atom_238Th,
		atom_239Th,
		atom_212Pa,
		atom_213Pa,
		atom_214Pa,
		atom_215Pa,
		atom_216Pa,
		atom_217Pa,
		atom_218Pa,
		atom_219Pa,
		atom_220Pa,
		atom_221Pa,
		atom_222Pa,
		atom_223Pa,
		atom_224Pa,
		atom_225Pa,
		atom_226Pa,
		atom_227Pa,
		atom_228Pa,
		atom_229Pa,
		atom_230Pa,
		atom_231Pa,
		atom_232Pa,
		atom_233Pa,
		atom_234Pa,
		atom_235Pa,
		atom_236Pa,
		atom_237Pa,
		atom_238Pa,
		atom_239Pa,
		atom_240Pa,
		atom_241Pa,
		atom_217U,
		atom_218U,
		atom_219U,
		atom_220U,
		atom_221U,
		atom_222U,
		atom_223U,
		atom_224U,
		atom_225U,
		atom_226U,
		atom_227U,
		atom_228U,
		atom_229U,
		atom_230U,
		atom_231U,
		atom_232U,
		atom_233U,
		atom_234U,
		atom_235U,
		atom_236U,
		atom_237U,
		atom_238U,
		atom_239U,
		atom_240U,
		atom_241U,
		atom_242U,
		atom_243U,
		atom_219Np,
		atom_220Np,
		atom_221Np,
		atom_222Np,
		atom_223Np,
		atom_224Np,
		atom_225Np,
		atom_226Np,
		atom_227Np,
		atom_228Np,
		atom_229Np,
		atom_230Np,
		atom_231Np,
		atom_232Np,
		atom_233Np,
		atom_234Np,
		atom_235Np,
		atom_236Np,
		atom_237Np,
		atom_238Np,
		atom_239Np,
		atom_240Np,
		atom_241Np,
		atom_242Np,
		atom_243Np,
		atom_244Np,
		atom_245Np,
		atom_228Pu,
		atom_229Pu,
		atom_230Pu,
		atom_231Pu,
		atom_232Pu,
		atom_233Pu,
		atom_234Pu,
		atom_235Pu,
		atom_236Pu,
		atom_237Pu,
		atom_238Pu,
		atom_239Pu,
		atom_240Pu,
		atom_241Pu,
		atom_242Pu,
		atom_243Pu,
		atom_244Pu,
		atom_245Pu,
		atom_246Pu,
		atom_247Pu,
		atom_230Am,
		atom_231Am,
		atom_232Am,
		atom_233Am,
		atom_234Am,
		atom_235Am,
		atom_236Am,
		atom_237Am,
		atom_238Am,
		atom_239Am,
		atom_240Am,
		atom_241Am,
		atom_242Am,
		atom_243Am,
		atom_244Am,
		atom_245Am,
		atom_246Am,
		atom_247Am,
		atom_248Am,
		atom_249Am,
		atom_232Cm,
		atom_233Cm,
		atom_234Cm,
		atom_235Cm,
		atom_236Cm,
		atom_237Cm,
		atom_238Cm,
		atom_239Cm,
		atom_240Cm,
		atom_241Cm,
		atom_242Cm,
		atom_243Cm,
		atom_244Cm,
		atom_245Cm,
		atom_246Cm,
		atom_247Cm,
		atom_248Cm,
		atom_249Cm,
		atom_250Cm,
		atom_251Cm,
		atom_252Cm,
		atom_234Bk,
		atom_235Bk,
		atom_236Bk,
		atom_237Bk,
		atom_238Bk,
		atom_239Bk,
		atom_240Bk,
		atom_241Bk,
		atom_242Bk,
		atom_243Bk,
		atom_244Bk,
		atom_245Bk,
		atom_246Bk,
		atom_247Bk,
		atom_248Bk,
		atom_249Bk,
		atom_250Bk,
		atom_251Bk,
		atom_252Bk,
		atom_253Bk,
		atom_254Bk,
		atom_237Cf,
		atom_238Cf,
		atom_239Cf,
		atom_240Cf,
		atom_241Cf,
		atom_242Cf,
		atom_243Cf,
		atom_244Cf,
		atom_245Cf,
		atom_246Cf,
		atom_247Cf,
		atom_248Cf,
		atom_249Cf,
		atom_250Cf,
		atom_251Cf,
		atom_252Cf,
		atom_253Cf,
		atom_254Cf,
		atom_255Cf,
		atom_256Cf,
		atom_239Es,
		atom_240Es,
		atom_241Es,
		atom_242Es,
		atom_243Es,
		atom_244Es,
		atom_245Es,
		atom_246Es,
		atom_247Es,
		atom_248Es,
		atom_249Es,
		atom_250Es,
		atom_251Es,
		atom_252Es,
		atom_253Es,
		atom_254Es,
		atom_255Es,
		atom_256Es,
		atom_257Es,
		atom_258Es,
		atom_241Fm,
		atom_242Fm,
		atom_243Fm,
		atom_244Fm,
		atom_245Fm,
		atom_246Fm,
		atom_247Fm,
		atom_248Fm,
		atom_249Fm,
		atom_250Fm,
		atom_251Fm,
		atom_252Fm,
		atom_253Fm,
		atom_254Fm,
		atom_255Fm,
		atom_256Fm,
		atom_257Fm,
		atom_258Fm,
		atom_259Fm,
		atom_260Fm,
		atom_245Md,
		atom_246Md,
		atom_247Md,
		atom_248Md,
		atom_249Md,
		atom_250Md,
		atom_251Md,
		atom_252Md,
		atom_253Md,
		atom_254Md,
		atom_255Md,
		atom_256Md,
		atom_257Md,
		atom_258Md,
		atom_259Md,
		atom_260Md,
		atom_261Md,
		atom_262Md,
		atom_248No,
		atom_249No,
		atom_250No,
		atom_251No,
		atom_252No,
		atom_253No,
		atom_254No,
		atom_255No,
		atom_256No,
		atom_257No,
		atom_258No,
		atom_259No,
		atom_260No,
		atom_261No,
		atom_262No,
		atom_263No,
		atom_264No,
		atom_251Lr,
		atom_252Lr,
		atom_253Lr,
		atom_254Lr,
		atom_255Lr,
		atom_256Lr,
		atom_257Lr,
		atom_258Lr,
		atom_259Lr,
		atom_260Lr,
		atom_261Lr,
		atom_262Lr,
		atom_263Lr,
		atom_264Lr,
		atom_265Lr,
		atom_266Lr,
		atom_253Rf,
		atom_254Rf,
		atom_255Rf,
		atom_256Rf,
		atom_257Rf,
		atom_258Rf,
		atom_259Rf,
		atom_260Rf,
		atom_261Rf,
		atom_262Rf,
		atom_263Rf,
		atom_264Rf,
		atom_265Rf,
		atom_266Rf,
		atom_267Rf,
		atom_268Rf,
		atom_255Db,
		atom_256Db,
		atom_257Db,
		atom_258Db,
		atom_259Db,
		atom_260Db,
		atom_261Db,
		atom_262Db,
		atom_263Db,
		atom_264Db,
		atom_265Db,
		atom_266Db,
		atom_267Db,
		atom_268Db,
		atom_269Db,
		atom_270Db,
		atom_258Sg,
		atom_259Sg,
		atom_260Sg,
		atom_261Sg,
		atom_262Sg,
		atom_263Sg,
		atom_264Sg,
		atom_265Sg,
		atom_266Sg,
		atom_267Sg,
		atom_268Sg,
		atom_269Sg,
		atom_270Sg,
		atom_271Sg,
		atom_272Sg,
		atom_273Sg,
		atom_260Bh,
		atom_261Bh,
		atom_262Bh,
		atom_263Bh,
		atom_264Bh,
		atom_265Bh,
		atom_266Bh,
		atom_267Bh,
		atom_268Bh,
		atom_269Bh,
		atom_270Bh,
		atom_271Bh,
		atom_272Bh,
		atom_273Bh,
		atom_274Bh,
		atom_275Bh,
		atom_263Hs,
		atom_264Hs,
		atom_265Hs,
		atom_266Hs,
		atom_267Hs,
		atom_268Hs,
		atom_269Hs,
		atom_270Hs,
		atom_271Hs,
		atom_272Hs,
		atom_273Hs,
		atom_274Hs,
		atom_275Hs,
		atom_276Hs,
		atom_277Hs,
		atom_265Mt,
		atom_266Mt,
		atom_267Mt,
		atom_268Mt,
		atom_269Mt,
		atom_270Mt,
		atom_271Mt,
		atom_272Mt,
		atom_273Mt,
		atom_274Mt,
		atom_275Mt,
		atom_276Mt,
		atom_277Mt,
		atom_278Mt,
		atom_279Mt,
		atom_267Ds,
		atom_268Ds,
		atom_269Ds,
		atom_270Ds,
		atom_271Ds,
		atom_272Ds,
		atom_273Ds,
		atom_274Ds,
		atom_275Ds,
		atom_276Ds,
		atom_277Ds,
		atom_278Ds,
		atom_279Ds,
		atom_280Ds,
		atom_281Ds,
		atom_272Rg,
		atom_273Rg,
		atom_274Rg,
		atom_275Rg,
		atom_276Rg,
		atom_277Rg,
		atom_278Rg,
		atom_279Rg,
		atom_280Rg,
		atom_281Rg,
		atom_282Rg,
		atom_283Rg,
		atom_276Cn,
		atom_277Cn,
		atom_278Cn,
		atom_279Cn,
		atom_280Cn,
		atom_281Cn,
		atom_282Cn,
		atom_283Cn,
		atom_284Cn,
		atom_285Cn,
		atom_278Nh,
		atom_279Nh,
		atom_280Nh,
		atom_281Nh,
		atom_282Nh,
		atom_283Nh,
		atom_284Nh,
		atom_285Nh,
		atom_286Nh,
		atom_287Nh,
		atom_285Fl,
		atom_286Fl,
		atom_287Fl,
		atom_288Fl,
		atom_289Fl,
		atom_287Mc,
		atom_288Mc,
		atom_289Mc,
		atom_290Mc,
		atom_291Uup,
		atom_289Lv,
		atom_290Lv,
		atom_291Lv,
		atom_292Lv,
		atom_293Lv,
		atom_291Ts,
		atom_292Ts,
		atom_293Ts,
		atom_294Uus,
		atom_293Og,
		atom_294Og,
		atom_295Og,
		atom_unknown
	};

	static constexpr usize MAX_ISOTOPE_COUNT = as_usize(nist::Isotope::atom_unknown);

	static constexpr c_str atomic_symbol(const nist::Isotope a)
	{
		switch (as_u16(a)) {
			case    0: return "1H\0";
			case    1: return "2H\0";
			case    2: return "3H\0";
			case    3: return "4H\0";
			case    4: return "5H\0";
			case    5: return "6H\0";
			case    6: return "7H\0";
			case    7: return "3He\0";
			case    8: return "4He\0";
			case    9: return "5He\0";
			case   10: return "6He\0";
			case   11: return "7He\0";
			case   12: return "8He\0";
			case   13: return "9He\0";
			case   14: return "10He\0";
			case   15: return "3Li\0";
			case   16: return "4Li\0";
			case   17: return "5Li\0";
			case   18: return "6Li\0";
			case   19: return "7Li\0";
			case   20: return "8Li\0";
			case   21: return "9Li\0";
			case   22: return "10Li\0";
			case   23: return "11Li\0";
			case   24: return "12Li\0";
			case   25: return "13Li\0";
			case   26: return "5Be\0";
			case   27: return "6Be\0";
			case   28: return "7Be\0";
			case   29: return "8Be\0";
			case   30: return "9Be\0";
			case   31: return "10Be\0";
			case   32: return "11Be\0";
			case   33: return "12Be\0";
			case   34: return "13Be\0";
			case   35: return "14Be\0";
			case   36: return "15Be\0";
			case   37: return "16Be\0";
			case   38: return "6B\0";
			case   39: return "7B\0";
			case   40: return "8B\0";
			case   41: return "9B\0";
			case   42: return "10B\0";
			case   43: return "11B\0";
			case   44: return "12B\0";
			case   45: return "13B\0";
			case   46: return "14B\0";
			case   47: return "15B\0";
			case   48: return "16B\0";
			case   49: return "17B\0";
			case   50: return "18B\0";
			case   51: return "19B\0";
			case   52: return "20B\0";
			case   53: return "21B\0";
			case   54: return "8C\0";
			case   55: return "9C\0";
			case   56: return "10C\0";
			case   57: return "11C\0";
			case   58: return "12C\0";
			case   59: return "13C\0";
			case   60: return "14C\0";
			case   61: return "15C\0";
			case   62: return "16C\0";
			case   63: return "17C\0";
			case   64: return "18C\0";
			case   65: return "19C\0";
			case   66: return "20C\0";
			case   67: return "21C\0";
			case   68: return "22C\0";
			case   69: return "23C\0";
			case   70: return "10N\0";
			case   71: return "11N\0";
			case   72: return "12N\0";
			case   73: return "13N\0";
			case   74: return "14N\0";
			case   75: return "15N\0";
			case   76: return "16N\0";
			case   77: return "17N\0";
			case   78: return "18N\0";
			case   79: return "19N\0";
			case   80: return "20N\0";
			case   81: return "21N\0";
			case   82: return "22N\0";
			case   83: return "23N\0";
			case   84: return "24N\0";
			case   85: return "25N\0";
			case   86: return "12O\0";
			case   87: return "13O\0";
			case   88: return "14O\0";
			case   89: return "15O\0";
			case   90: return "16O\0";
			case   91: return "17O\0";
			case   92: return "18O\0";
			case   93: return "19O\0";
			case   94: return "20O\0";
			case   95: return "21O\0";
			case   96: return "22O\0";
			case   97: return "23O\0";
			case   98: return "24O\0";
			case   99: return "25O\0";
			case  100: return "26O\0";
			case  101: return "27O\0";
			case  102: return "28O\0";
			case  103: return "14F\0";
			case  104: return "15F\0";
			case  105: return "16F\0";
			case  106: return "17F\0";
			case  107: return "18F\0";
			case  108: return "19F\0";
			case  109: return "20F\0";
			case  110: return "21F\0";
			case  111: return "22F\0";
			case  112: return "23F\0";
			case  113: return "24F\0";
			case  114: return "25F\0";
			case  115: return "26F\0";
			case  116: return "27F\0";
			case  117: return "28F\0";
			case  118: return "29F\0";
			case  119: return "30F\0";
			case  120: return "31F\0";
			case  121: return "16Ne\0";
			case  122: return "17Ne\0";
			case  123: return "18Ne\0";
			case  124: return "19Ne\0";
			case  125: return "20Ne\0";
			case  126: return "21Ne\0";
			case  127: return "22Ne\0";
			case  128: return "23Ne\0";
			case  129: return "24Ne\0";
			case  130: return "25Ne\0";
			case  131: return "26Ne\0";
			case  132: return "27Ne\0";
			case  133: return "28Ne\0";
			case  134: return "29Ne\0";
			case  135: return "30Ne\0";
			case  136: return "31Ne\0";
			case  137: return "32Ne\0";
			case  138: return "33Ne\0";
			case  139: return "34Ne\0";
			case  140: return "18Na\0";
			case  141: return "19Na\0";
			case  142: return "20Na\0";
			case  143: return "21Na\0";
			case  144: return "22Na\0";
			case  145: return "23Na\0";
			case  146: return "24Na\0";
			case  147: return "25Na\0";
			case  148: return "26Na\0";
			case  149: return "27Na\0";
			case  150: return "28Na\0";
			case  151: return "29Na\0";
			case  152: return "30Na\0";
			case  153: return "31Na\0";
			case  154: return "32Na\0";
			case  155: return "33Na\0";
			case  156: return "34Na\0";
			case  157: return "35Na\0";
			case  158: return "36Na\0";
			case  159: return "37Na\0";
			case  160: return "19Mg\0";
			case  161: return "20Mg\0";
			case  162: return "21Mg\0";
			case  163: return "22Mg\0";
			case  164: return "23Mg\0";
			case  165: return "24Mg\0";
			case  166: return "25Mg\0";
			case  167: return "26Mg\0";
			case  168: return "27Mg\0";
			case  169: return "28Mg\0";
			case  170: return "29Mg\0";
			case  171: return "30Mg\0";
			case  172: return "31Mg\0";
			case  173: return "32Mg\0";
			case  174: return "33Mg\0";
			case  175: return "34Mg\0";
			case  176: return "35Mg\0";
			case  177: return "36Mg\0";
			case  178: return "37Mg\0";
			case  179: return "38Mg\0";
			case  180: return "39Mg\0";
			case  181: return "40Mg\0";
			case  182: return "21Al\0";
			case  183: return "22Al\0";
			case  184: return "23Al\0";
			case  185: return "24Al\0";
			case  186: return "25Al\0";
			case  187: return "26Al\0";
			case  188: return "27Al\0";
			case  189: return "28Al\0";
			case  190: return "29Al\0";
			case  191: return "30Al\0";
			case  192: return "31Al\0";
			case  193: return "32Al\0";
			case  194: return "33Al\0";
			case  195: return "34Al\0";
			case  196: return "35Al\0";
			case  197: return "36Al\0";
			case  198: return "37Al\0";
			case  199: return "38Al\0";
			case  200: return "39Al\0";
			case  201: return "40Al\0";
			case  202: return "41Al\0";
			case  203: return "42Al\0";
			case  204: return "43Al\0";
			case  205: return "22Si\0";
			case  206: return "23Si\0";
			case  207: return "24Si\0";
			case  208: return "25Si\0";
			case  209: return "26Si\0";
			case  210: return "27Si\0";
			case  211: return "28Si\0";
			case  212: return "29Si\0";
			case  213: return "30Si\0";
			case  214: return "31Si\0";
			case  215: return "32Si\0";
			case  216: return "33Si\0";
			case  217: return "34Si\0";
			case  218: return "35Si\0";
			case  219: return "36Si\0";
			case  220: return "37Si\0";
			case  221: return "38Si\0";
			case  222: return "39Si\0";
			case  223: return "40Si\0";
			case  224: return "41Si\0";
			case  225: return "42Si\0";
			case  226: return "43Si\0";
			case  227: return "44Si\0";
			case  228: return "45Si\0";
			case  229: return "24P\0";
			case  230: return "25P\0";
			case  231: return "26P\0";
			case  232: return "27P\0";
			case  233: return "28P\0";
			case  234: return "29P\0";
			case  235: return "30P\0";
			case  236: return "31P\0";
			case  237: return "32P\0";
			case  238: return "33P\0";
			case  239: return "34P\0";
			case  240: return "35P\0";
			case  241: return "36P\0";
			case  242: return "37P\0";
			case  243: return "38P\0";
			case  244: return "39P\0";
			case  245: return "40P\0";
			case  246: return "41P\0";
			case  247: return "42P\0";
			case  248: return "43P\0";
			case  249: return "44P\0";
			case  250: return "45P\0";
			case  251: return "46P\0";
			case  252: return "47P\0";
			case  253: return "26S\0";
			case  254: return "27S\0";
			case  255: return "28S\0";
			case  256: return "29S\0";
			case  257: return "30S\0";
			case  258: return "31S\0";
			case  259: return "32S\0";
			case  260: return "33S\0";
			case  261: return "34S\0";
			case  262: return "35S\0";
			case  263: return "36S\0";
			case  264: return "37S\0";
			case  265: return "38S\0";
			case  266: return "39S\0";
			case  267: return "40S\0";
			case  268: return "41S\0";
			case  269: return "42S\0";
			case  270: return "43S\0";
			case  271: return "44S\0";
			case  272: return "45S\0";
			case  273: return "46S\0";
			case  274: return "47S\0";
			case  275: return "48S\0";
			case  276: return "49S\0";
			case  277: return "28Cl\0";
			case  278: return "29Cl\0";
			case  279: return "30Cl\0";
			case  280: return "31Cl\0";
			case  281: return "32Cl\0";
			case  282: return "33Cl\0";
			case  283: return "34Cl\0";
			case  284: return "35Cl\0";
			case  285: return "36Cl\0";
			case  286: return "37Cl\0";
			case  287: return "38Cl\0";
			case  288: return "39Cl\0";
			case  289: return "40Cl\0";
			case  290: return "41Cl\0";
			case  291: return "42Cl\0";
			case  292: return "43Cl\0";
			case  293: return "44Cl\0";
			case  294: return "45Cl\0";
			case  295: return "46Cl\0";
			case  296: return "47Cl\0";
			case  297: return "48Cl\0";
			case  298: return "49Cl\0";
			case  299: return "50Cl\0";
			case  300: return "51Cl\0";
			case  301: return "30Ar\0";
			case  302: return "31Ar\0";
			case  303: return "32Ar\0";
			case  304: return "33Ar\0";
			case  305: return "34Ar\0";
			case  306: return "35Ar\0";
			case  307: return "36Ar\0";
			case  308: return "37Ar\0";
			case  309: return "38Ar\0";
			case  310: return "39Ar\0";
			case  311: return "40Ar\0";
			case  312: return "41Ar\0";
			case  313: return "42Ar\0";
			case  314: return "43Ar\0";
			case  315: return "44Ar\0";
			case  316: return "45Ar\0";
			case  317: return "46Ar\0";
			case  318: return "47Ar\0";
			case  319: return "48Ar\0";
			case  320: return "49Ar\0";
			case  321: return "50Ar\0";
			case  322: return "51Ar\0";
			case  323: return "52Ar\0";
			case  324: return "53Ar\0";
			case  325: return "32K\0";
			case  326: return "33K\0";
			case  327: return "34K\0";
			case  328: return "35K\0";
			case  329: return "36K\0";
			case  330: return "37K\0";
			case  331: return "38K\0";
			case  332: return "39K\0";
			case  333: return "40K\0";
			case  334: return "41K\0";
			case  335: return "42K\0";
			case  336: return "43K\0";
			case  337: return "44K\0";
			case  338: return "45K\0";
			case  339: return "46K\0";
			case  340: return "47K\0";
			case  341: return "48K\0";
			case  342: return "49K\0";
			case  343: return "50K\0";
			case  344: return "51K\0";
			case  345: return "52K\0";
			case  346: return "53K\0";
			case  347: return "54K\0";
			case  348: return "55K\0";
			case  349: return "56K\0";
			case  350: return "34Ca\0";
			case  351: return "35Ca\0";
			case  352: return "36Ca\0";
			case  353: return "37Ca\0";
			case  354: return "38Ca\0";
			case  355: return "39Ca\0";
			case  356: return "40Ca\0";
			case  357: return "41Ca\0";
			case  358: return "42Ca\0";
			case  359: return "43Ca\0";
			case  360: return "44Ca\0";
			case  361: return "45Ca\0";
			case  362: return "46Ca\0";
			case  363: return "47Ca\0";
			case  364: return "48Ca\0";
			case  365: return "49Ca\0";
			case  366: return "50Ca\0";
			case  367: return "51Ca\0";
			case  368: return "52Ca\0";
			case  369: return "53Ca\0";
			case  370: return "54Ca\0";
			case  371: return "55Ca\0";
			case  372: return "56Ca\0";
			case  373: return "57Ca\0";
			case  374: return "58Ca\0";
			case  375: return "36Sc\0";
			case  376: return "37Sc\0";
			case  377: return "38Sc\0";
			case  378: return "39Sc\0";
			case  379: return "40Sc\0";
			case  380: return "41Sc\0";
			case  381: return "42Sc\0";
			case  382: return "43Sc\0";
			case  383: return "44Sc\0";
			case  384: return "45Sc\0";
			case  385: return "46Sc\0";
			case  386: return "47Sc\0";
			case  387: return "48Sc\0";
			case  388: return "49Sc\0";
			case  389: return "50Sc\0";
			case  390: return "51Sc\0";
			case  391: return "52Sc\0";
			case  392: return "53Sc\0";
			case  393: return "54Sc\0";
			case  394: return "55Sc\0";
			case  395: return "56Sc\0";
			case  396: return "57Sc\0";
			case  397: return "58Sc\0";
			case  398: return "59Sc\0";
			case  399: return "60Sc\0";
			case  400: return "61Sc\0";
			case  401: return "38Ti\0";
			case  402: return "39Ti\0";
			case  403: return "40Ti\0";
			case  404: return "41Ti\0";
			case  405: return "42Ti\0";
			case  406: return "43Ti\0";
			case  407: return "44Ti\0";
			case  408: return "45Ti\0";
			case  409: return "46Ti\0";
			case  410: return "47Ti\0";
			case  411: return "48Ti\0";
			case  412: return "49Ti\0";
			case  413: return "50Ti\0";
			case  414: return "51Ti\0";
			case  415: return "52Ti\0";
			case  416: return "53Ti\0";
			case  417: return "54Ti\0";
			case  418: return "55Ti\0";
			case  419: return "56Ti\0";
			case  420: return "57Ti\0";
			case  421: return "58Ti\0";
			case  422: return "59Ti\0";
			case  423: return "60Ti\0";
			case  424: return "61Ti\0";
			case  425: return "62Ti\0";
			case  426: return "63Ti\0";
			case  427: return "40V\0";
			case  428: return "41V\0";
			case  429: return "42V\0";
			case  430: return "43V\0";
			case  431: return "44V\0";
			case  432: return "45V\0";
			case  433: return "46V\0";
			case  434: return "47V\0";
			case  435: return "48V\0";
			case  436: return "49V\0";
			case  437: return "50V\0";
			case  438: return "51V\0";
			case  439: return "52V\0";
			case  440: return "53V\0";
			case  441: return "54V\0";
			case  442: return "55V\0";
			case  443: return "56V\0";
			case  444: return "57V\0";
			case  445: return "58V\0";
			case  446: return "59V\0";
			case  447: return "60V\0";
			case  448: return "61V\0";
			case  449: return "62V\0";
			case  450: return "63V\0";
			case  451: return "64V\0";
			case  452: return "65V\0";
			case  453: return "66V\0";
			case  454: return "42Cr\0";
			case  455: return "43Cr\0";
			case  456: return "44Cr\0";
			case  457: return "45Cr\0";
			case  458: return "46Cr\0";
			case  459: return "47Cr\0";
			case  460: return "48Cr\0";
			case  461: return "49Cr\0";
			case  462: return "50Cr\0";
			case  463: return "51Cr\0";
			case  464: return "52Cr\0";
			case  465: return "53Cr\0";
			case  466: return "54Cr\0";
			case  467: return "55Cr\0";
			case  468: return "56Cr\0";
			case  469: return "57Cr\0";
			case  470: return "58Cr\0";
			case  471: return "59Cr\0";
			case  472: return "60Cr\0";
			case  473: return "61Cr\0";
			case  474: return "62Cr\0";
			case  475: return "63Cr\0";
			case  476: return "64Cr\0";
			case  477: return "65Cr\0";
			case  478: return "66Cr\0";
			case  479: return "67Cr\0";
			case  480: return "68Cr\0";
			case  481: return "44Mn\0";
			case  482: return "45Mn\0";
			case  483: return "46Mn\0";
			case  484: return "47Mn\0";
			case  485: return "48Mn\0";
			case  486: return "49Mn\0";
			case  487: return "50Mn\0";
			case  488: return "51Mn\0";
			case  489: return "52Mn\0";
			case  490: return "53Mn\0";
			case  491: return "54Mn\0";
			case  492: return "55Mn\0";
			case  493: return "56Mn\0";
			case  494: return "57Mn\0";
			case  495: return "58Mn\0";
			case  496: return "59Mn\0";
			case  497: return "60Mn\0";
			case  498: return "61Mn\0";
			case  499: return "62Mn\0";
			case  500: return "63Mn\0";
			case  501: return "64Mn\0";
			case  502: return "65Mn\0";
			case  503: return "66Mn\0";
			case  504: return "67Mn\0";
			case  505: return "68Mn\0";
			case  506: return "69Mn\0";
			case  507: return "70Mn\0";
			case  508: return "71Mn\0";
			case  509: return "45Fe\0";
			case  510: return "46Fe\0";
			case  511: return "47Fe\0";
			case  512: return "48Fe\0";
			case  513: return "49Fe\0";
			case  514: return "50Fe\0";
			case  515: return "51Fe\0";
			case  516: return "52Fe\0";
			case  517: return "53Fe\0";
			case  518: return "54Fe\0";
			case  519: return "55Fe\0";
			case  520: return "56Fe\0";
			case  521: return "57Fe\0";
			case  522: return "58Fe\0";
			case  523: return "59Fe\0";
			case  524: return "60Fe\0";
			case  525: return "61Fe\0";
			case  526: return "62Fe\0";
			case  527: return "63Fe\0";
			case  528: return "64Fe\0";
			case  529: return "65Fe\0";
			case  530: return "66Fe\0";
			case  531: return "67Fe\0";
			case  532: return "68Fe\0";
			case  533: return "69Fe\0";
			case  534: return "70Fe\0";
			case  535: return "71Fe\0";
			case  536: return "72Fe\0";
			case  537: return "73Fe\0";
			case  538: return "74Fe\0";
			case  539: return "47Co\0";
			case  540: return "48Co\0";
			case  541: return "49Co\0";
			case  542: return "50Co\0";
			case  543: return "51Co\0";
			case  544: return "52Co\0";
			case  545: return "53Co\0";
			case  546: return "54Co\0";
			case  547: return "55Co\0";
			case  548: return "56Co\0";
			case  549: return "57Co\0";
			case  550: return "58Co\0";
			case  551: return "59Co\0";
			case  552: return "60Co\0";
			case  553: return "61Co\0";
			case  554: return "62Co\0";
			case  555: return "63Co\0";
			case  556: return "64Co\0";
			case  557: return "65Co\0";
			case  558: return "66Co\0";
			case  559: return "67Co\0";
			case  560: return "68Co\0";
			case  561: return "69Co\0";
			case  562: return "70Co\0";
			case  563: return "71Co\0";
			case  564: return "72Co\0";
			case  565: return "73Co\0";
			case  566: return "74Co\0";
			case  567: return "75Co\0";
			case  568: return "76Co\0";
			case  569: return "48Ni\0";
			case  570: return "49Ni\0";
			case  571: return "50Ni\0";
			case  572: return "51Ni\0";
			case  573: return "52Ni\0";
			case  574: return "53Ni\0";
			case  575: return "54Ni\0";
			case  576: return "55Ni\0";
			case  577: return "56Ni\0";
			case  578: return "57Ni\0";
			case  579: return "58Ni\0";
			case  580: return "59Ni\0";
			case  581: return "60Ni\0";
			case  582: return "61Ni\0";
			case  583: return "62Ni\0";
			case  584: return "63Ni\0";
			case  585: return "64Ni\0";
			case  586: return "65Ni\0";
			case  587: return "66Ni\0";
			case  588: return "67Ni\0";
			case  589: return "68Ni\0";
			case  590: return "69Ni\0";
			case  591: return "70Ni\0";
			case  592: return "71Ni\0";
			case  593: return "72Ni\0";
			case  594: return "73Ni\0";
			case  595: return "74Ni\0";
			case  596: return "75Ni\0";
			case  597: return "76Ni\0";
			case  598: return "77Ni\0";
			case  599: return "78Ni\0";
			case  600: return "79Ni\0";
			case  601: return "52Cu\0";
			case  602: return "53Cu\0";
			case  603: return "54Cu\0";
			case  604: return "55Cu\0";
			case  605: return "56Cu\0";
			case  606: return "57Cu\0";
			case  607: return "58Cu\0";
			case  608: return "59Cu\0";
			case  609: return "60Cu\0";
			case  610: return "61Cu\0";
			case  611: return "62Cu\0";
			case  612: return "63Cu\0";
			case  613: return "64Cu\0";
			case  614: return "65Cu\0";
			case  615: return "66Cu\0";
			case  616: return "67Cu\0";
			case  617: return "68Cu\0";
			case  618: return "69Cu\0";
			case  619: return "70Cu\0";
			case  620: return "71Cu\0";
			case  621: return "72Cu\0";
			case  622: return "73Cu\0";
			case  623: return "74Cu\0";
			case  624: return "75Cu\0";
			case  625: return "76Cu\0";
			case  626: return "77Cu\0";
			case  627: return "78Cu\0";
			case  628: return "79Cu\0";
			case  629: return "80Cu\0";
			case  630: return "81Cu\0";
			case  631: return "82Cu\0";
			case  632: return "54Zn\0";
			case  633: return "55Zn\0";
			case  634: return "56Zn\0";
			case  635: return "57Zn\0";
			case  636: return "58Zn\0";
			case  637: return "59Zn\0";
			case  638: return "60Zn\0";
			case  639: return "61Zn\0";
			case  640: return "62Zn\0";
			case  641: return "63Zn\0";
			case  642: return "64Zn\0";
			case  643: return "65Zn\0";
			case  644: return "66Zn\0";
			case  645: return "67Zn\0";
			case  646: return "68Zn\0";
			case  647: return "69Zn\0";
			case  648: return "70Zn\0";
			case  649: return "71Zn\0";
			case  650: return "72Zn\0";
			case  651: return "73Zn\0";
			case  652: return "74Zn\0";
			case  653: return "75Zn\0";
			case  654: return "76Zn\0";
			case  655: return "77Zn\0";
			case  656: return "78Zn\0";
			case  657: return "79Zn\0";
			case  658: return "80Zn\0";
			case  659: return "81Zn\0";
			case  660: return "82Zn\0";
			case  661: return "83Zn\0";
			case  662: return "84Zn\0";
			case  663: return "85Zn\0";
			case  664: return "56Ga\0";
			case  665: return "57Ga\0";
			case  666: return "58Ga\0";
			case  667: return "59Ga\0";
			case  668: return "60Ga\0";
			case  669: return "61Ga\0";
			case  670: return "62Ga\0";
			case  671: return "63Ga\0";
			case  672: return "64Ga\0";
			case  673: return "65Ga\0";
			case  674: return "66Ga\0";
			case  675: return "67Ga\0";
			case  676: return "68Ga\0";
			case  677: return "69Ga\0";
			case  678: return "70Ga\0";
			case  679: return "71Ga\0";
			case  680: return "72Ga\0";
			case  681: return "73Ga\0";
			case  682: return "74Ga\0";
			case  683: return "75Ga\0";
			case  684: return "76Ga\0";
			case  685: return "77Ga\0";
			case  686: return "78Ga\0";
			case  687: return "79Ga\0";
			case  688: return "80Ga\0";
			case  689: return "81Ga\0";
			case  690: return "82Ga\0";
			case  691: return "83Ga\0";
			case  692: return "84Ga\0";
			case  693: return "85Ga\0";
			case  694: return "86Ga\0";
			case  695: return "87Ga\0";
			case  696: return "58Ge\0";
			case  697: return "59Ge\0";
			case  698: return "60Ge\0";
			case  699: return "61Ge\0";
			case  700: return "62Ge\0";
			case  701: return "63Ge\0";
			case  702: return "64Ge\0";
			case  703: return "65Ge\0";
			case  704: return "66Ge\0";
			case  705: return "67Ge\0";
			case  706: return "68Ge\0";
			case  707: return "69Ge\0";
			case  708: return "70Ge\0";
			case  709: return "71Ge\0";
			case  710: return "72Ge\0";
			case  711: return "73Ge\0";
			case  712: return "74Ge\0";
			case  713: return "75Ge\0";
			case  714: return "76Ge\0";
			case  715: return "77Ge\0";
			case  716: return "78Ge\0";
			case  717: return "79Ge\0";
			case  718: return "80Ge\0";
			case  719: return "81Ge\0";
			case  720: return "82Ge\0";
			case  721: return "83Ge\0";
			case  722: return "84Ge\0";
			case  723: return "85Ge\0";
			case  724: return "86Ge\0";
			case  725: return "87Ge\0";
			case  726: return "88Ge\0";
			case  727: return "89Ge\0";
			case  728: return "90Ge\0";
			case  729: return "60As\0";
			case  730: return "61As\0";
			case  731: return "62As\0";
			case  732: return "63As\0";
			case  733: return "64As\0";
			case  734: return "65As\0";
			case  735: return "66As\0";
			case  736: return "67As\0";
			case  737: return "68As\0";
			case  738: return "69As\0";
			case  739: return "70As\0";
			case  740: return "71As\0";
			case  741: return "72As\0";
			case  742: return "73As\0";
			case  743: return "74As\0";
			case  744: return "75As\0";
			case  745: return "76As\0";
			case  746: return "77As\0";
			case  747: return "78As\0";
			case  748: return "79As\0";
			case  749: return "80As\0";
			case  750: return "81As\0";
			case  751: return "82As\0";
			case  752: return "83As\0";
			case  753: return "84As\0";
			case  754: return "85As\0";
			case  755: return "86As\0";
			case  756: return "87As\0";
			case  757: return "88As\0";
			case  758: return "89As\0";
			case  759: return "90As\0";
			case  760: return "91As\0";
			case  761: return "92As\0";
			case  762: return "64Se\0";
			case  763: return "65Se\0";
			case  764: return "66Se\0";
			case  765: return "67Se\0";
			case  766: return "68Se\0";
			case  767: return "69Se\0";
			case  768: return "70Se\0";
			case  769: return "71Se\0";
			case  770: return "72Se\0";
			case  771: return "73Se\0";
			case  772: return "74Se\0";
			case  773: return "75Se\0";
			case  774: return "76Se\0";
			case  775: return "77Se\0";
			case  776: return "78Se\0";
			case  777: return "79Se\0";
			case  778: return "80Se\0";
			case  779: return "81Se\0";
			case  780: return "82Se\0";
			case  781: return "83Se\0";
			case  782: return "84Se\0";
			case  783: return "85Se\0";
			case  784: return "86Se\0";
			case  785: return "87Se\0";
			case  786: return "88Se\0";
			case  787: return "89Se\0";
			case  788: return "90Se\0";
			case  789: return "91Se\0";
			case  790: return "92Se\0";
			case  791: return "93Se\0";
			case  792: return "94Se\0";
			case  793: return "95Se\0";
			case  794: return "67Br\0";
			case  795: return "68Br\0";
			case  796: return "69Br\0";
			case  797: return "70Br\0";
			case  798: return "71Br\0";
			case  799: return "72Br\0";
			case  800: return "73Br\0";
			case  801: return "74Br\0";
			case  802: return "75Br\0";
			case  803: return "76Br\0";
			case  804: return "77Br\0";
			case  805: return "78Br\0";
			case  806: return "79Br\0";
			case  807: return "80Br\0";
			case  808: return "81Br\0";
			case  809: return "82Br\0";
			case  810: return "83Br\0";
			case  811: return "84Br\0";
			case  812: return "85Br\0";
			case  813: return "86Br\0";
			case  814: return "87Br\0";
			case  815: return "88Br\0";
			case  816: return "89Br\0";
			case  817: return "90Br\0";
			case  818: return "91Br\0";
			case  819: return "92Br\0";
			case  820: return "93Br\0";
			case  821: return "94Br\0";
			case  822: return "95Br\0";
			case  823: return "96Br\0";
			case  824: return "97Br\0";
			case  825: return "98Br\0";
			case  826: return "69Kr\0";
			case  827: return "70Kr\0";
			case  828: return "71Kr\0";
			case  829: return "72Kr\0";
			case  830: return "73Kr\0";
			case  831: return "74Kr\0";
			case  832: return "75Kr\0";
			case  833: return "76Kr\0";
			case  834: return "77Kr\0";
			case  835: return "78Kr\0";
			case  836: return "79Kr\0";
			case  837: return "80Kr\0";
			case  838: return "81Kr\0";
			case  839: return "82Kr\0";
			case  840: return "83Kr\0";
			case  841: return "84Kr\0";
			case  842: return "85Kr\0";
			case  843: return "86Kr\0";
			case  844: return "87Kr\0";
			case  845: return "88Kr\0";
			case  846: return "89Kr\0";
			case  847: return "90Kr\0";
			case  848: return "91Kr\0";
			case  849: return "92Kr\0";
			case  850: return "93Kr\0";
			case  851: return "94Kr\0";
			case  852: return "95Kr\0";
			case  853: return "96Kr\0";
			case  854: return "97Kr\0";
			case  855: return "98Kr\0";
			case  856: return "99Kr\0";
			case  857: return "100Kr\0";
			case  858: return "101Kr\0";
			case  859: return "71Rb\0";
			case  860: return "72Rb\0";
			case  861: return "73Rb\0";
			case  862: return "74Rb\0";
			case  863: return "75Rb\0";
			case  864: return "76Rb\0";
			case  865: return "77Rb\0";
			case  866: return "78Rb\0";
			case  867: return "79Rb\0";
			case  868: return "80Rb\0";
			case  869: return "81Rb\0";
			case  870: return "82Rb\0";
			case  871: return "83Rb\0";
			case  872: return "84Rb\0";
			case  873: return "85Rb\0";
			case  874: return "86Rb\0";
			case  875: return "87Rb\0";
			case  876: return "88Rb\0";
			case  877: return "89Rb\0";
			case  878: return "90Rb\0";
			case  879: return "91Rb\0";
			case  880: return "92Rb\0";
			case  881: return "93Rb\0";
			case  882: return "94Rb\0";
			case  883: return "95Rb\0";
			case  884: return "96Rb\0";
			case  885: return "97Rb\0";
			case  886: return "98Rb\0";
			case  887: return "99Rb\0";
			case  888: return "100Rb\0";
			case  889: return "101Rb\0";
			case  890: return "102Rb\0";
			case  891: return "103Rb\0";
			case  892: return "73Sr\0";
			case  893: return "74Sr\0";
			case  894: return "75Sr\0";
			case  895: return "76Sr\0";
			case  896: return "77Sr\0";
			case  897: return "78Sr\0";
			case  898: return "79Sr\0";
			case  899: return "80Sr\0";
			case  900: return "81Sr\0";
			case  901: return "82Sr\0";
			case  902: return "83Sr\0";
			case  903: return "84Sr\0";
			case  904: return "85Sr\0";
			case  905: return "86Sr\0";
			case  906: return "87Sr\0";
			case  907: return "88Sr\0";
			case  908: return "89Sr\0";
			case  909: return "90Sr\0";
			case  910: return "91Sr\0";
			case  911: return "92Sr\0";
			case  912: return "93Sr\0";
			case  913: return "94Sr\0";
			case  914: return "95Sr\0";
			case  915: return "96Sr\0";
			case  916: return "97Sr\0";
			case  917: return "98Sr\0";
			case  918: return "99Sr\0";
			case  919: return "100Sr\0";
			case  920: return "101Sr\0";
			case  921: return "102Sr\0";
			case  922: return "103Sr\0";
			case  923: return "104Sr\0";
			case  924: return "105Sr\0";
			case  925: return "106Sr\0";
			case  926: return "107Sr\0";
			case  927: return "76Y\0";
			case  928: return "77Y\0";
			case  929: return "78Y\0";
			case  930: return "79Y\0";
			case  931: return "80Y\0";
			case  932: return "81Y\0";
			case  933: return "82Y\0";
			case  934: return "83Y\0";
			case  935: return "84Y\0";
			case  936: return "85Y\0";
			case  937: return "86Y\0";
			case  938: return "87Y\0";
			case  939: return "88Y\0";
			case  940: return "89Y\0";
			case  941: return "90Y\0";
			case  942: return "91Y\0";
			case  943: return "92Y\0";
			case  944: return "93Y\0";
			case  945: return "94Y\0";
			case  946: return "95Y\0";
			case  947: return "96Y\0";
			case  948: return "97Y\0";
			case  949: return "98Y\0";
			case  950: return "99Y\0";
			case  951: return "100Y\0";
			case  952: return "101Y\0";
			case  953: return "102Y\0";
			case  954: return "103Y\0";
			case  955: return "104Y\0";
			case  956: return "105Y\0";
			case  957: return "106Y\0";
			case  958: return "107Y\0";
			case  959: return "108Y\0";
			case  960: return "109Y\0";
			case  961: return "78Zr\0";
			case  962: return "79Zr\0";
			case  963: return "80Zr\0";
			case  964: return "81Zr\0";
			case  965: return "82Zr\0";
			case  966: return "83Zr\0";
			case  967: return "84Zr\0";
			case  968: return "85Zr\0";
			case  969: return "86Zr\0";
			case  970: return "87Zr\0";
			case  971: return "88Zr\0";
			case  972: return "89Zr\0";
			case  973: return "90Zr\0";
			case  974: return "91Zr\0";
			case  975: return "92Zr\0";
			case  976: return "93Zr\0";
			case  977: return "94Zr\0";
			case  978: return "95Zr\0";
			case  979: return "96Zr\0";
			case  980: return "97Zr\0";
			case  981: return "98Zr\0";
			case  982: return "99Zr\0";
			case  983: return "100Zr\0";
			case  984: return "101Zr\0";
			case  985: return "102Zr\0";
			case  986: return "103Zr\0";
			case  987: return "104Zr\0";
			case  988: return "105Zr\0";
			case  989: return "106Zr\0";
			case  990: return "107Zr\0";
			case  991: return "108Zr\0";
			case  992: return "109Zr\0";
			case  993: return "110Zr\0";
			case  994: return "111Zr\0";
			case  995: return "112Zr\0";
			case  996: return "81Nb\0";
			case  997: return "82Nb\0";
			case  998: return "83Nb\0";
			case  999: return "84Nb\0";
			case 1000: return "85Nb\0";
			case 1001: return "86Nb\0";
			case 1002: return "87Nb\0";
			case 1003: return "88Nb\0";
			case 1004: return "89Nb\0";
			case 1005: return "90Nb\0";
			case 1006: return "91Nb\0";
			case 1007: return "92Nb\0";
			case 1008: return "93Nb\0";
			case 1009: return "94Nb\0";
			case 1010: return "95Nb\0";
			case 1011: return "96Nb\0";
			case 1012: return "97Nb\0";
			case 1013: return "98Nb\0";
			case 1014: return "99Nb\0";
			case 1015: return "100Nb\0";
			case 1016: return "101Nb\0";
			case 1017: return "102Nb\0";
			case 1018: return "103Nb\0";
			case 1019: return "104Nb\0";
			case 1020: return "105Nb\0";
			case 1021: return "106Nb\0";
			case 1022: return "107Nb\0";
			case 1023: return "108Nb\0";
			case 1024: return "109Nb\0";
			case 1025: return "110Nb\0";
			case 1026: return "111Nb\0";
			case 1027: return "112Nb\0";
			case 1028: return "113Nb\0";
			case 1029: return "114Nb\0";
			case 1030: return "115Nb\0";
			case 1031: return "83Mo\0";
			case 1032: return "84Mo\0";
			case 1033: return "85Mo\0";
			case 1034: return "86Mo\0";
			case 1035: return "87Mo\0";
			case 1036: return "88Mo\0";
			case 1037: return "89Mo\0";
			case 1038: return "90Mo\0";
			case 1039: return "91Mo\0";
			case 1040: return "92Mo\0";
			case 1041: return "93Mo\0";
			case 1042: return "94Mo\0";
			case 1043: return "95Mo\0";
			case 1044: return "96Mo\0";
			case 1045: return "97Mo\0";
			case 1046: return "98Mo\0";
			case 1047: return "99Mo\0";
			case 1048: return "100Mo\0";
			case 1049: return "101Mo\0";
			case 1050: return "102Mo\0";
			case 1051: return "103Mo\0";
			case 1052: return "104Mo\0";
			case 1053: return "105Mo\0";
			case 1054: return "106Mo\0";
			case 1055: return "107Mo\0";
			case 1056: return "108Mo\0";
			case 1057: return "109Mo\0";
			case 1058: return "110Mo\0";
			case 1059: return "111Mo\0";
			case 1060: return "112Mo\0";
			case 1061: return "113Mo\0";
			case 1062: return "114Mo\0";
			case 1063: return "115Mo\0";
			case 1064: return "116Mo\0";
			case 1065: return "117Mo\0";
			case 1066: return "85Tc\0";
			case 1067: return "86Tc\0";
			case 1068: return "87Tc\0";
			case 1069: return "88Tc\0";
			case 1070: return "89Tc\0";
			case 1071: return "90Tc\0";
			case 1072: return "91Tc\0";
			case 1073: return "92Tc\0";
			case 1074: return "93Tc\0";
			case 1075: return "94Tc\0";
			case 1076: return "95Tc\0";
			case 1077: return "96Tc\0";
			case 1078: return "97Tc\0";
			case 1079: return "98Tc\0";
			case 1080: return "99Tc\0";
			case 1081: return "100Tc\0";
			case 1082: return "101Tc\0";
			case 1083: return "102Tc\0";
			case 1084: return "103Tc\0";
			case 1085: return "104Tc\0";
			case 1086: return "105Tc\0";
			case 1087: return "106Tc\0";
			case 1088: return "107Tc\0";
			case 1089: return "108Tc\0";
			case 1090: return "109Tc\0";
			case 1091: return "110Tc\0";
			case 1092: return "111Tc\0";
			case 1093: return "112Tc\0";
			case 1094: return "113Tc\0";
			case 1095: return "114Tc\0";
			case 1096: return "115Tc\0";
			case 1097: return "116Tc\0";
			case 1098: return "117Tc\0";
			case 1099: return "118Tc\0";
			case 1100: return "119Tc\0";
			case 1101: return "120Tc\0";
			case 1102: return "87Ru\0";
			case 1103: return "88Ru\0";
			case 1104: return "89Ru\0";
			case 1105: return "90Ru\0";
			case 1106: return "91Ru\0";
			case 1107: return "92Ru\0";
			case 1108: return "93Ru\0";
			case 1109: return "94Ru\0";
			case 1110: return "95Ru\0";
			case 1111: return "96Ru\0";
			case 1112: return "97Ru\0";
			case 1113: return "98Ru\0";
			case 1114: return "99Ru\0";
			case 1115: return "100Ru\0";
			case 1116: return "101Ru\0";
			case 1117: return "102Ru\0";
			case 1118: return "103Ru\0";
			case 1119: return "104Ru\0";
			case 1120: return "105Ru\0";
			case 1121: return "106Ru\0";
			case 1122: return "107Ru\0";
			case 1123: return "108Ru\0";
			case 1124: return "109Ru\0";
			case 1125: return "110Ru\0";
			case 1126: return "111Ru\0";
			case 1127: return "112Ru\0";
			case 1128: return "113Ru\0";
			case 1129: return "114Ru\0";
			case 1130: return "115Ru\0";
			case 1131: return "116Ru\0";
			case 1132: return "117Ru\0";
			case 1133: return "118Ru\0";
			case 1134: return "119Ru\0";
			case 1135: return "120Ru\0";
			case 1136: return "121Ru\0";
			case 1137: return "122Ru\0";
			case 1138: return "123Ru\0";
			case 1139: return "124Ru\0";
			case 1140: return "89Rh\0";
			case 1141: return "90Rh\0";
			case 1142: return "91Rh\0";
			case 1143: return "92Rh\0";
			case 1144: return "93Rh\0";
			case 1145: return "94Rh\0";
			case 1146: return "95Rh\0";
			case 1147: return "96Rh\0";
			case 1148: return "97Rh\0";
			case 1149: return "98Rh\0";
			case 1150: return "99Rh\0";
			case 1151: return "100Rh\0";
			case 1152: return "101Rh\0";
			case 1153: return "102Rh\0";
			case 1154: return "103Rh\0";
			case 1155: return "104Rh\0";
			case 1156: return "105Rh\0";
			case 1157: return "106Rh\0";
			case 1158: return "107Rh\0";
			case 1159: return "108Rh\0";
			case 1160: return "109Rh\0";
			case 1161: return "110Rh\0";
			case 1162: return "111Rh\0";
			case 1163: return "112Rh\0";
			case 1164: return "113Rh\0";
			case 1165: return "114Rh\0";
			case 1166: return "115Rh\0";
			case 1167: return "116Rh\0";
			case 1168: return "117Rh\0";
			case 1169: return "118Rh\0";
			case 1170: return "119Rh\0";
			case 1171: return "120Rh\0";
			case 1172: return "121Rh\0";
			case 1173: return "122Rh\0";
			case 1174: return "123Rh\0";
			case 1175: return "124Rh\0";
			case 1176: return "125Rh\0";
			case 1177: return "126Rh\0";
			case 1178: return "91Pd\0";
			case 1179: return "92Pd\0";
			case 1180: return "93Pd\0";
			case 1181: return "94Pd\0";
			case 1182: return "95Pd\0";
			case 1183: return "96Pd\0";
			case 1184: return "97Pd\0";
			case 1185: return "98Pd\0";
			case 1186: return "99Pd\0";
			case 1187: return "100Pd\0";
			case 1188: return "101Pd\0";
			case 1189: return "102Pd\0";
			case 1190: return "103Pd\0";
			case 1191: return "104Pd\0";
			case 1192: return "105Pd\0";
			case 1193: return "106Pd\0";
			case 1194: return "107Pd\0";
			case 1195: return "108Pd\0";
			case 1196: return "109Pd\0";
			case 1197: return "110Pd\0";
			case 1198: return "111Pd\0";
			case 1199: return "112Pd\0";
			case 1200: return "113Pd\0";
			case 1201: return "114Pd\0";
			case 1202: return "115Pd\0";
			case 1203: return "116Pd\0";
			case 1204: return "117Pd\0";
			case 1205: return "118Pd\0";
			case 1206: return "119Pd\0";
			case 1207: return "120Pd\0";
			case 1208: return "121Pd\0";
			case 1209: return "122Pd\0";
			case 1210: return "123Pd\0";
			case 1211: return "124Pd\0";
			case 1212: return "125Pd\0";
			case 1213: return "126Pd\0";
			case 1214: return "127Pd\0";
			case 1215: return "128Pd\0";
			case 1216: return "93Ag\0";
			case 1217: return "94Ag\0";
			case 1218: return "95Ag\0";
			case 1219: return "96Ag\0";
			case 1220: return "97Ag\0";
			case 1221: return "98Ag\0";
			case 1222: return "99Ag\0";
			case 1223: return "100Ag\0";
			case 1224: return "101Ag\0";
			case 1225: return "102Ag\0";
			case 1226: return "103Ag\0";
			case 1227: return "104Ag\0";
			case 1228: return "105Ag\0";
			case 1229: return "106Ag\0";
			case 1230: return "107Ag\0";
			case 1231: return "108Ag\0";
			case 1232: return "109Ag\0";
			case 1233: return "110Ag\0";
			case 1234: return "111Ag\0";
			case 1235: return "112Ag\0";
			case 1236: return "113Ag\0";
			case 1237: return "114Ag\0";
			case 1238: return "115Ag\0";
			case 1239: return "116Ag\0";
			case 1240: return "117Ag\0";
			case 1241: return "118Ag\0";
			case 1242: return "119Ag\0";
			case 1243: return "120Ag\0";
			case 1244: return "121Ag\0";
			case 1245: return "122Ag\0";
			case 1246: return "123Ag\0";
			case 1247: return "124Ag\0";
			case 1248: return "125Ag\0";
			case 1249: return "126Ag\0";
			case 1250: return "127Ag\0";
			case 1251: return "128Ag\0";
			case 1252: return "129Ag\0";
			case 1253: return "130Ag\0";
			case 1254: return "95Cd\0";
			case 1255: return "96Cd\0";
			case 1256: return "97Cd\0";
			case 1257: return "98Cd\0";
			case 1258: return "99Cd\0";
			case 1259: return "100Cd\0";
			case 1260: return "101Cd\0";
			case 1261: return "102Cd\0";
			case 1262: return "103Cd\0";
			case 1263: return "104Cd\0";
			case 1264: return "105Cd\0";
			case 1265: return "106Cd\0";
			case 1266: return "107Cd\0";
			case 1267: return "108Cd\0";
			case 1268: return "109Cd\0";
			case 1269: return "110Cd\0";
			case 1270: return "111Cd\0";
			case 1271: return "112Cd\0";
			case 1272: return "113Cd\0";
			case 1273: return "114Cd\0";
			case 1274: return "115Cd\0";
			case 1275: return "116Cd\0";
			case 1276: return "117Cd\0";
			case 1277: return "118Cd\0";
			case 1278: return "119Cd\0";
			case 1279: return "120Cd\0";
			case 1280: return "121Cd\0";
			case 1281: return "122Cd\0";
			case 1282: return "123Cd\0";
			case 1283: return "124Cd\0";
			case 1284: return "125Cd\0";
			case 1285: return "126Cd\0";
			case 1286: return "127Cd\0";
			case 1287: return "128Cd\0";
			case 1288: return "129Cd\0";
			case 1289: return "130Cd\0";
			case 1290: return "131Cd\0";
			case 1291: return "132Cd\0";
			case 1292: return "133Cd\0";
			case 1293: return "97In\0";
			case 1294: return "98In\0";
			case 1295: return "99In\0";
			case 1296: return "100In\0";
			case 1297: return "101In\0";
			case 1298: return "102In\0";
			case 1299: return "103In\0";
			case 1300: return "104In\0";
			case 1301: return "105In\0";
			case 1302: return "106In\0";
			case 1303: return "107In\0";
			case 1304: return "108In\0";
			case 1305: return "109In\0";
			case 1306: return "110In\0";
			case 1307: return "111In\0";
			case 1308: return "112In\0";
			case 1309: return "113In\0";
			case 1310: return "114In\0";
			case 1311: return "115In\0";
			case 1312: return "116In\0";
			case 1313: return "117In\0";
			case 1314: return "118In\0";
			case 1315: return "119In\0";
			case 1316: return "120In\0";
			case 1317: return "121In\0";
			case 1318: return "122In\0";
			case 1319: return "123In\0";
			case 1320: return "124In\0";
			case 1321: return "125In\0";
			case 1322: return "126In\0";
			case 1323: return "127In\0";
			case 1324: return "128In\0";
			case 1325: return "129In\0";
			case 1326: return "130In\0";
			case 1327: return "131In\0";
			case 1328: return "132In\0";
			case 1329: return "133In\0";
			case 1330: return "134In\0";
			case 1331: return "135In\0";
			case 1332: return "99Sn\0";
			case 1333: return "100Sn\0";
			case 1334: return "101Sn\0";
			case 1335: return "102Sn\0";
			case 1336: return "103Sn\0";
			case 1337: return "104Sn\0";
			case 1338: return "105Sn\0";
			case 1339: return "106Sn\0";
			case 1340: return "107Sn\0";
			case 1341: return "108Sn\0";
			case 1342: return "109Sn\0";
			case 1343: return "110Sn\0";
			case 1344: return "111Sn\0";
			case 1345: return "112Sn\0";
			case 1346: return "113Sn\0";
			case 1347: return "114Sn\0";
			case 1348: return "115Sn\0";
			case 1349: return "116Sn\0";
			case 1350: return "117Sn\0";
			case 1351: return "118Sn\0";
			case 1352: return "119Sn\0";
			case 1353: return "120Sn\0";
			case 1354: return "121Sn\0";
			case 1355: return "122Sn\0";
			case 1356: return "123Sn\0";
			case 1357: return "124Sn\0";
			case 1358: return "125Sn\0";
			case 1359: return "126Sn\0";
			case 1360: return "127Sn\0";
			case 1361: return "128Sn\0";
			case 1362: return "129Sn\0";
			case 1363: return "130Sn\0";
			case 1364: return "131Sn\0";
			case 1365: return "132Sn\0";
			case 1366: return "133Sn\0";
			case 1367: return "134Sn\0";
			case 1368: return "135Sn\0";
			case 1369: return "136Sn\0";
			case 1370: return "137Sn\0";
			case 1371: return "138Sn\0";
			case 1372: return "103Sb\0";
			case 1373: return "104Sb\0";
			case 1374: return "105Sb\0";
			case 1375: return "106Sb\0";
			case 1376: return "107Sb\0";
			case 1377: return "108Sb\0";
			case 1378: return "109Sb\0";
			case 1379: return "110Sb\0";
			case 1380: return "111Sb\0";
			case 1381: return "112Sb\0";
			case 1382: return "113Sb\0";
			case 1383: return "114Sb\0";
			case 1384: return "115Sb\0";
			case 1385: return "116Sb\0";
			case 1386: return "117Sb\0";
			case 1387: return "118Sb\0";
			case 1388: return "119Sb\0";
			case 1389: return "120Sb\0";
			case 1390: return "121Sb\0";
			case 1391: return "122Sb\0";
			case 1392: return "123Sb\0";
			case 1393: return "124Sb\0";
			case 1394: return "125Sb\0";
			case 1395: return "126Sb\0";
			case 1396: return "127Sb\0";
			case 1397: return "128Sb\0";
			case 1398: return "129Sb\0";
			case 1399: return "130Sb\0";
			case 1400: return "131Sb\0";
			case 1401: return "132Sb\0";
			case 1402: return "133Sb\0";
			case 1403: return "134Sb\0";
			case 1404: return "135Sb\0";
			case 1405: return "136Sb\0";
			case 1406: return "137Sb\0";
			case 1407: return "138Sb\0";
			case 1408: return "139Sb\0";
			case 1409: return "140Sb\0";
			case 1410: return "105Te\0";
			case 1411: return "106Te\0";
			case 1412: return "107Te\0";
			case 1413: return "108Te\0";
			case 1414: return "109Te\0";
			case 1415: return "110Te\0";
			case 1416: return "111Te\0";
			case 1417: return "112Te\0";
			case 1418: return "113Te\0";
			case 1419: return "114Te\0";
			case 1420: return "115Te\0";
			case 1421: return "116Te\0";
			case 1422: return "117Te\0";
			case 1423: return "118Te\0";
			case 1424: return "119Te\0";
			case 1425: return "120Te\0";
			case 1426: return "121Te\0";
			case 1427: return "122Te\0";
			case 1428: return "123Te\0";
			case 1429: return "124Te\0";
			case 1430: return "125Te\0";
			case 1431: return "126Te\0";
			case 1432: return "127Te\0";
			case 1433: return "128Te\0";
			case 1434: return "129Te\0";
			case 1435: return "130Te\0";
			case 1436: return "131Te\0";
			case 1437: return "132Te\0";
			case 1438: return "133Te\0";
			case 1439: return "134Te\0";
			case 1440: return "135Te\0";
			case 1441: return "136Te\0";
			case 1442: return "137Te\0";
			case 1443: return "138Te\0";
			case 1444: return "139Te\0";
			case 1445: return "140Te\0";
			case 1446: return "141Te\0";
			case 1447: return "142Te\0";
			case 1448: return "143Te\0";
			case 1449: return "107I\0";
			case 1450: return "108I\0";
			case 1451: return "109I\0";
			case 1452: return "110I\0";
			case 1453: return "111I\0";
			case 1454: return "112I\0";
			case 1455: return "113I\0";
			case 1456: return "114I\0";
			case 1457: return "115I\0";
			case 1458: return "116I\0";
			case 1459: return "117I\0";
			case 1460: return "118I\0";
			case 1461: return "119I\0";
			case 1462: return "120I\0";
			case 1463: return "121I\0";
			case 1464: return "122I\0";
			case 1465: return "123I\0";
			case 1466: return "124I\0";
			case 1467: return "125I\0";
			case 1468: return "126I\0";
			case 1469: return "127I\0";
			case 1470: return "128I\0";
			case 1471: return "129I\0";
			case 1472: return "130I\0";
			case 1473: return "131I\0";
			case 1474: return "132I\0";
			case 1475: return "133I\0";
			case 1476: return "134I\0";
			case 1477: return "135I\0";
			case 1478: return "136I\0";
			case 1479: return "137I\0";
			case 1480: return "138I\0";
			case 1481: return "139I\0";
			case 1482: return "140I\0";
			case 1483: return "141I\0";
			case 1484: return "142I\0";
			case 1485: return "143I\0";
			case 1486: return "144I\0";
			case 1487: return "145I\0";
			case 1488: return "109Xe\0";
			case 1489: return "110Xe\0";
			case 1490: return "111Xe\0";
			case 1491: return "112Xe\0";
			case 1492: return "113Xe\0";
			case 1493: return "114Xe\0";
			case 1494: return "115Xe\0";
			case 1495: return "116Xe\0";
			case 1496: return "117Xe\0";
			case 1497: return "118Xe\0";
			case 1498: return "119Xe\0";
			case 1499: return "120Xe\0";
			case 1500: return "121Xe\0";
			case 1501: return "122Xe\0";
			case 1502: return "123Xe\0";
			case 1503: return "124Xe\0";
			case 1504: return "125Xe\0";
			case 1505: return "126Xe\0";
			case 1506: return "127Xe\0";
			case 1507: return "128Xe\0";
			case 1508: return "129Xe\0";
			case 1509: return "130Xe\0";
			case 1510: return "131Xe\0";
			case 1511: return "132Xe\0";
			case 1512: return "133Xe\0";
			case 1513: return "134Xe\0";
			case 1514: return "135Xe\0";
			case 1515: return "136Xe\0";
			case 1516: return "137Xe\0";
			case 1517: return "138Xe\0";
			case 1518: return "139Xe\0";
			case 1519: return "140Xe\0";
			case 1520: return "141Xe\0";
			case 1521: return "142Xe\0";
			case 1522: return "143Xe\0";
			case 1523: return "144Xe\0";
			case 1524: return "145Xe\0";
			case 1525: return "146Xe\0";
			case 1526: return "147Xe\0";
			case 1527: return "148Xe\0";
			case 1528: return "112Cs\0";
			case 1529: return "113Cs\0";
			case 1530: return "114Cs\0";
			case 1531: return "115Cs\0";
			case 1532: return "116Cs\0";
			case 1533: return "117Cs\0";
			case 1534: return "118Cs\0";
			case 1535: return "119Cs\0";
			case 1536: return "120Cs\0";
			case 1537: return "121Cs\0";
			case 1538: return "122Cs\0";
			case 1539: return "123Cs\0";
			case 1540: return "124Cs\0";
			case 1541: return "125Cs\0";
			case 1542: return "126Cs\0";
			case 1543: return "127Cs\0";
			case 1544: return "128Cs\0";
			case 1545: return "129Cs\0";
			case 1546: return "130Cs\0";
			case 1547: return "131Cs\0";
			case 1548: return "132Cs\0";
			case 1549: return "133Cs\0";
			case 1550: return "134Cs\0";
			case 1551: return "135Cs\0";
			case 1552: return "136Cs\0";
			case 1553: return "137Cs\0";
			case 1554: return "138Cs\0";
			case 1555: return "139Cs\0";
			case 1556: return "140Cs\0";
			case 1557: return "141Cs\0";
			case 1558: return "142Cs\0";
			case 1559: return "143Cs\0";
			case 1560: return "144Cs\0";
			case 1561: return "145Cs\0";
			case 1562: return "146Cs\0";
			case 1563: return "147Cs\0";
			case 1564: return "148Cs\0";
			case 1565: return "149Cs\0";
			case 1566: return "150Cs\0";
			case 1567: return "151Cs\0";
			case 1568: return "114Ba\0";
			case 1569: return "115Ba\0";
			case 1570: return "116Ba\0";
			case 1571: return "117Ba\0";
			case 1572: return "118Ba\0";
			case 1573: return "119Ba\0";
			case 1574: return "120Ba\0";
			case 1575: return "121Ba\0";
			case 1576: return "122Ba\0";
			case 1577: return "123Ba\0";
			case 1578: return "124Ba\0";
			case 1579: return "125Ba\0";
			case 1580: return "126Ba\0";
			case 1581: return "127Ba\0";
			case 1582: return "128Ba\0";
			case 1583: return "129Ba\0";
			case 1584: return "130Ba\0";
			case 1585: return "131Ba\0";
			case 1586: return "132Ba\0";
			case 1587: return "133Ba\0";
			case 1588: return "134Ba\0";
			case 1589: return "135Ba\0";
			case 1590: return "136Ba\0";
			case 1591: return "137Ba\0";
			case 1592: return "138Ba\0";
			case 1593: return "139Ba\0";
			case 1594: return "140Ba\0";
			case 1595: return "141Ba\0";
			case 1596: return "142Ba\0";
			case 1597: return "143Ba\0";
			case 1598: return "144Ba\0";
			case 1599: return "145Ba\0";
			case 1600: return "146Ba\0";
			case 1601: return "147Ba\0";
			case 1602: return "148Ba\0";
			case 1603: return "149Ba\0";
			case 1604: return "150Ba\0";
			case 1605: return "151Ba\0";
			case 1606: return "152Ba\0";
			case 1607: return "153Ba\0";
			case 1608: return "116La\0";
			case 1609: return "117La\0";
			case 1610: return "118La\0";
			case 1611: return "119La\0";
			case 1612: return "120La\0";
			case 1613: return "121La\0";
			case 1614: return "122La\0";
			case 1615: return "123La\0";
			case 1616: return "124La\0";
			case 1617: return "125La\0";
			case 1618: return "126La\0";
			case 1619: return "127La\0";
			case 1620: return "128La\0";
			case 1621: return "129La\0";
			case 1622: return "130La\0";
			case 1623: return "131La\0";
			case 1624: return "132La\0";
			case 1625: return "133La\0";
			case 1626: return "134La\0";
			case 1627: return "135La\0";
			case 1628: return "136La\0";
			case 1629: return "137La\0";
			case 1630: return "138La\0";
			case 1631: return "139La\0";
			case 1632: return "140La\0";
			case 1633: return "141La\0";
			case 1634: return "142La\0";
			case 1635: return "143La\0";
			case 1636: return "144La\0";
			case 1637: return "145La\0";
			case 1638: return "146La\0";
			case 1639: return "147La\0";
			case 1640: return "148La\0";
			case 1641: return "149La\0";
			case 1642: return "150La\0";
			case 1643: return "151La\0";
			case 1644: return "152La\0";
			case 1645: return "153La\0";
			case 1646: return "154La\0";
			case 1647: return "155La\0";
			case 1648: return "119Ce\0";
			case 1649: return "120Ce\0";
			case 1650: return "121Ce\0";
			case 1651: return "122Ce\0";
			case 1652: return "123Ce\0";
			case 1653: return "124Ce\0";
			case 1654: return "125Ce\0";
			case 1655: return "126Ce\0";
			case 1656: return "127Ce\0";
			case 1657: return "128Ce\0";
			case 1658: return "129Ce\0";
			case 1659: return "130Ce\0";
			case 1660: return "131Ce\0";
			case 1661: return "132Ce\0";
			case 1662: return "133Ce\0";
			case 1663: return "134Ce\0";
			case 1664: return "135Ce\0";
			case 1665: return "136Ce\0";
			case 1666: return "137Ce\0";
			case 1667: return "138Ce\0";
			case 1668: return "139Ce\0";
			case 1669: return "140Ce\0";
			case 1670: return "141Ce\0";
			case 1671: return "142Ce\0";
			case 1672: return "143Ce\0";
			case 1673: return "144Ce\0";
			case 1674: return "145Ce\0";
			case 1675: return "146Ce\0";
			case 1676: return "147Ce\0";
			case 1677: return "148Ce\0";
			case 1678: return "149Ce\0";
			case 1679: return "150Ce\0";
			case 1680: return "151Ce\0";
			case 1681: return "152Ce\0";
			case 1682: return "153Ce\0";
			case 1683: return "154Ce\0";
			case 1684: return "155Ce\0";
			case 1685: return "156Ce\0";
			case 1686: return "157Ce\0";
			case 1687: return "121Pr\0";
			case 1688: return "122Pr\0";
			case 1689: return "123Pr\0";
			case 1690: return "124Pr\0";
			case 1691: return "125Pr\0";
			case 1692: return "126Pr\0";
			case 1693: return "127Pr\0";
			case 1694: return "128Pr\0";
			case 1695: return "129Pr\0";
			case 1696: return "130Pr\0";
			case 1697: return "131Pr\0";
			case 1698: return "132Pr\0";
			case 1699: return "133Pr\0";
			case 1700: return "134Pr\0";
			case 1701: return "135Pr\0";
			case 1702: return "136Pr\0";
			case 1703: return "137Pr\0";
			case 1704: return "138Pr\0";
			case 1705: return "139Pr\0";
			case 1706: return "140Pr\0";
			case 1707: return "141Pr\0";
			case 1708: return "142Pr\0";
			case 1709: return "143Pr\0";
			case 1710: return "144Pr\0";
			case 1711: return "145Pr\0";
			case 1712: return "146Pr\0";
			case 1713: return "147Pr\0";
			case 1714: return "148Pr\0";
			case 1715: return "149Pr\0";
			case 1716: return "150Pr\0";
			case 1717: return "151Pr\0";
			case 1718: return "152Pr\0";
			case 1719: return "153Pr\0";
			case 1720: return "154Pr\0";
			case 1721: return "155Pr\0";
			case 1722: return "156Pr\0";
			case 1723: return "157Pr\0";
			case 1724: return "158Pr\0";
			case 1725: return "159Pr\0";
			case 1726: return "124Nd\0";
			case 1727: return "125Nd\0";
			case 1728: return "126Nd\0";
			case 1729: return "127Nd\0";
			case 1730: return "128Nd\0";
			case 1731: return "129Nd\0";
			case 1732: return "130Nd\0";
			case 1733: return "131Nd\0";
			case 1734: return "132Nd\0";
			case 1735: return "133Nd\0";
			case 1736: return "134Nd\0";
			case 1737: return "135Nd\0";
			case 1738: return "136Nd\0";
			case 1739: return "137Nd\0";
			case 1740: return "138Nd\0";
			case 1741: return "139Nd\0";
			case 1742: return "140Nd\0";
			case 1743: return "141Nd\0";
			case 1744: return "142Nd\0";
			case 1745: return "143Nd\0";
			case 1746: return "144Nd\0";
			case 1747: return "145Nd\0";
			case 1748: return "146Nd\0";
			case 1749: return "147Nd\0";
			case 1750: return "148Nd\0";
			case 1751: return "149Nd\0";
			case 1752: return "150Nd\0";
			case 1753: return "151Nd\0";
			case 1754: return "152Nd\0";
			case 1755: return "153Nd\0";
			case 1756: return "154Nd\0";
			case 1757: return "155Nd\0";
			case 1758: return "156Nd\0";
			case 1759: return "157Nd\0";
			case 1760: return "158Nd\0";
			case 1761: return "159Nd\0";
			case 1762: return "160Nd\0";
			case 1763: return "161Nd\0";
			case 1764: return "126Pm\0";
			case 1765: return "127Pm\0";
			case 1766: return "128Pm\0";
			case 1767: return "129Pm\0";
			case 1768: return "130Pm\0";
			case 1769: return "131Pm\0";
			case 1770: return "132Pm\0";
			case 1771: return "133Pm\0";
			case 1772: return "134Pm\0";
			case 1773: return "135Pm\0";
			case 1774: return "136Pm\0";
			case 1775: return "137Pm\0";
			case 1776: return "138Pm\0";
			case 1777: return "139Pm\0";
			case 1778: return "140Pm\0";
			case 1779: return "141Pm\0";
			case 1780: return "142Pm\0";
			case 1781: return "143Pm\0";
			case 1782: return "144Pm\0";
			case 1783: return "145Pm\0";
			case 1784: return "146Pm\0";
			case 1785: return "147Pm\0";
			case 1786: return "148Pm\0";
			case 1787: return "149Pm\0";
			case 1788: return "150Pm\0";
			case 1789: return "151Pm\0";
			case 1790: return "152Pm\0";
			case 1791: return "153Pm\0";
			case 1792: return "154Pm\0";
			case 1793: return "155Pm\0";
			case 1794: return "156Pm\0";
			case 1795: return "157Pm\0";
			case 1796: return "158Pm\0";
			case 1797: return "159Pm\0";
			case 1798: return "160Pm\0";
			case 1799: return "161Pm\0";
			case 1800: return "162Pm\0";
			case 1801: return "163Pm\0";
			case 1802: return "128Sm\0";
			case 1803: return "129Sm\0";
			case 1804: return "130Sm\0";
			case 1805: return "131Sm\0";
			case 1806: return "132Sm\0";
			case 1807: return "133Sm\0";
			case 1808: return "134Sm\0";
			case 1809: return "135Sm\0";
			case 1810: return "136Sm\0";
			case 1811: return "137Sm\0";
			case 1812: return "138Sm\0";
			case 1813: return "139Sm\0";
			case 1814: return "140Sm\0";
			case 1815: return "141Sm\0";
			case 1816: return "142Sm\0";
			case 1817: return "143Sm\0";
			case 1818: return "144Sm\0";
			case 1819: return "145Sm\0";
			case 1820: return "146Sm\0";
			case 1821: return "147Sm\0";
			case 1822: return "148Sm\0";
			case 1823: return "149Sm\0";
			case 1824: return "150Sm\0";
			case 1825: return "151Sm\0";
			case 1826: return "152Sm\0";
			case 1827: return "153Sm\0";
			case 1828: return "154Sm\0";
			case 1829: return "155Sm\0";
			case 1830: return "156Sm\0";
			case 1831: return "157Sm\0";
			case 1832: return "158Sm\0";
			case 1833: return "159Sm\0";
			case 1834: return "160Sm\0";
			case 1835: return "161Sm\0";
			case 1836: return "162Sm\0";
			case 1837: return "163Sm\0";
			case 1838: return "164Sm\0";
			case 1839: return "165Sm\0";
			case 1840: return "130Eu\0";
			case 1841: return "131Eu\0";
			case 1842: return "132Eu\0";
			case 1843: return "133Eu\0";
			case 1844: return "134Eu\0";
			case 1845: return "135Eu\0";
			case 1846: return "136Eu\0";
			case 1847: return "137Eu\0";
			case 1848: return "138Eu\0";
			case 1849: return "139Eu\0";
			case 1850: return "140Eu\0";
			case 1851: return "141Eu\0";
			case 1852: return "142Eu\0";
			case 1853: return "143Eu\0";
			case 1854: return "144Eu\0";
			case 1855: return "145Eu\0";
			case 1856: return "146Eu\0";
			case 1857: return "147Eu\0";
			case 1858: return "148Eu\0";
			case 1859: return "149Eu\0";
			case 1860: return "150Eu\0";
			case 1861: return "151Eu\0";
			case 1862: return "152Eu\0";
			case 1863: return "153Eu\0";
			case 1864: return "154Eu\0";
			case 1865: return "155Eu\0";
			case 1866: return "156Eu\0";
			case 1867: return "157Eu\0";
			case 1868: return "158Eu\0";
			case 1869: return "159Eu\0";
			case 1870: return "160Eu\0";
			case 1871: return "161Eu\0";
			case 1872: return "162Eu\0";
			case 1873: return "163Eu\0";
			case 1874: return "164Eu\0";
			case 1875: return "165Eu\0";
			case 1876: return "166Eu\0";
			case 1877: return "167Eu\0";
			case 1878: return "133Gd\0";
			case 1879: return "134Gd\0";
			case 1880: return "135Gd\0";
			case 1881: return "136Gd\0";
			case 1882: return "137Gd\0";
			case 1883: return "138Gd\0";
			case 1884: return "139Gd\0";
			case 1885: return "140Gd\0";
			case 1886: return "141Gd\0";
			case 1887: return "142Gd\0";
			case 1888: return "143Gd\0";
			case 1889: return "144Gd\0";
			case 1890: return "145Gd\0";
			case 1891: return "146Gd\0";
			case 1892: return "147Gd\0";
			case 1893: return "148Gd\0";
			case 1894: return "149Gd\0";
			case 1895: return "150Gd\0";
			case 1896: return "151Gd\0";
			case 1897: return "152Gd\0";
			case 1898: return "153Gd\0";
			case 1899: return "154Gd\0";
			case 1900: return "155Gd\0";
			case 1901: return "156Gd\0";
			case 1902: return "157Gd\0";
			case 1903: return "158Gd\0";
			case 1904: return "159Gd\0";
			case 1905: return "160Gd\0";
			case 1906: return "161Gd\0";
			case 1907: return "162Gd\0";
			case 1908: return "163Gd\0";
			case 1909: return "164Gd\0";
			case 1910: return "165Gd\0";
			case 1911: return "166Gd\0";
			case 1912: return "167Gd\0";
			case 1913: return "168Gd\0";
			case 1914: return "169Gd\0";
			case 1915: return "135Tb\0";
			case 1916: return "136Tb\0";
			case 1917: return "137Tb\0";
			case 1918: return "138Tb\0";
			case 1919: return "139Tb\0";
			case 1920: return "140Tb\0";
			case 1921: return "141Tb\0";
			case 1922: return "142Tb\0";
			case 1923: return "143Tb\0";
			case 1924: return "144Tb\0";
			case 1925: return "145Tb\0";
			case 1926: return "146Tb\0";
			case 1927: return "147Tb\0";
			case 1928: return "148Tb\0";
			case 1929: return "149Tb\0";
			case 1930: return "150Tb\0";
			case 1931: return "151Tb\0";
			case 1932: return "152Tb\0";
			case 1933: return "153Tb\0";
			case 1934: return "154Tb\0";
			case 1935: return "155Tb\0";
			case 1936: return "156Tb\0";
			case 1937: return "157Tb\0";
			case 1938: return "158Tb\0";
			case 1939: return "159Tb\0";
			case 1940: return "160Tb\0";
			case 1941: return "161Tb\0";
			case 1942: return "162Tb\0";
			case 1943: return "163Tb\0";
			case 1944: return "164Tb\0";
			case 1945: return "165Tb\0";
			case 1946: return "166Tb\0";
			case 1947: return "167Tb\0";
			case 1948: return "168Tb\0";
			case 1949: return "169Tb\0";
			case 1950: return "170Tb\0";
			case 1951: return "171Tb\0";
			case 1952: return "138Dy\0";
			case 1953: return "139Dy\0";
			case 1954: return "140Dy\0";
			case 1955: return "141Dy\0";
			case 1956: return "142Dy\0";
			case 1957: return "143Dy\0";
			case 1958: return "144Dy\0";
			case 1959: return "145Dy\0";
			case 1960: return "146Dy\0";
			case 1961: return "147Dy\0";
			case 1962: return "148Dy\0";
			case 1963: return "149Dy\0";
			case 1964: return "150Dy\0";
			case 1965: return "151Dy\0";
			case 1966: return "152Dy\0";
			case 1967: return "153Dy\0";
			case 1968: return "154Dy\0";
			case 1969: return "155Dy\0";
			case 1970: return "156Dy\0";
			case 1971: return "157Dy\0";
			case 1972: return "158Dy\0";
			case 1973: return "159Dy\0";
			case 1974: return "160Dy\0";
			case 1975: return "161Dy\0";
			case 1976: return "162Dy\0";
			case 1977: return "163Dy\0";
			case 1978: return "164Dy\0";
			case 1979: return "165Dy\0";
			case 1980: return "166Dy\0";
			case 1981: return "167Dy\0";
			case 1982: return "168Dy\0";
			case 1983: return "169Dy\0";
			case 1984: return "170Dy\0";
			case 1985: return "171Dy\0";
			case 1986: return "172Dy\0";
			case 1987: return "173Dy\0";
			case 1988: return "140Ho\0";
			case 1989: return "141Ho\0";
			case 1990: return "142Ho\0";
			case 1991: return "143Ho\0";
			case 1992: return "144Ho\0";
			case 1993: return "145Ho\0";
			case 1994: return "146Ho\0";
			case 1995: return "147Ho\0";
			case 1996: return "148Ho\0";
			case 1997: return "149Ho\0";
			case 1998: return "150Ho\0";
			case 1999: return "151Ho\0";
			case 2000: return "152Ho\0";
			case 2001: return "153Ho\0";
			case 2002: return "154Ho\0";
			case 2003: return "155Ho\0";
			case 2004: return "156Ho\0";
			case 2005: return "157Ho\0";
			case 2006: return "158Ho\0";
			case 2007: return "159Ho\0";
			case 2008: return "160Ho\0";
			case 2009: return "161Ho\0";
			case 2010: return "162Ho\0";
			case 2011: return "163Ho\0";
			case 2012: return "164Ho\0";
			case 2013: return "165Ho\0";
			case 2014: return "166Ho\0";
			case 2015: return "167Ho\0";
			case 2016: return "168Ho\0";
			case 2017: return "169Ho\0";
			case 2018: return "170Ho\0";
			case 2019: return "171Ho\0";
			case 2020: return "172Ho\0";
			case 2021: return "173Ho\0";
			case 2022: return "174Ho\0";
			case 2023: return "175Ho\0";
			case 2024: return "142Er\0";
			case 2025: return "143Er\0";
			case 2026: return "144Er\0";
			case 2027: return "145Er\0";
			case 2028: return "146Er\0";
			case 2029: return "147Er\0";
			case 2030: return "148Er\0";
			case 2031: return "149Er\0";
			case 2032: return "150Er\0";
			case 2033: return "151Er\0";
			case 2034: return "152Er\0";
			case 2035: return "153Er\0";
			case 2036: return "154Er\0";
			case 2037: return "155Er\0";
			case 2038: return "156Er\0";
			case 2039: return "157Er\0";
			case 2040: return "158Er\0";
			case 2041: return "159Er\0";
			case 2042: return "160Er\0";
			case 2043: return "161Er\0";
			case 2044: return "162Er\0";
			case 2045: return "163Er\0";
			case 2046: return "164Er\0";
			case 2047: return "165Er\0";
			case 2048: return "166Er\0";
			case 2049: return "167Er\0";
			case 2050: return "168Er\0";
			case 2051: return "169Er\0";
			case 2052: return "170Er\0";
			case 2053: return "171Er\0";
			case 2054: return "172Er\0";
			case 2055: return "173Er\0";
			case 2056: return "174Er\0";
			case 2057: return "175Er\0";
			case 2058: return "176Er\0";
			case 2059: return "177Er\0";
			case 2060: return "144Tm\0";
			case 2061: return "145Tm\0";
			case 2062: return "146Tm\0";
			case 2063: return "147Tm\0";
			case 2064: return "148Tm\0";
			case 2065: return "149Tm\0";
			case 2066: return "150Tm\0";
			case 2067: return "151Tm\0";
			case 2068: return "152Tm\0";
			case 2069: return "153Tm\0";
			case 2070: return "154Tm\0";
			case 2071: return "155Tm\0";
			case 2072: return "156Tm\0";
			case 2073: return "157Tm\0";
			case 2074: return "158Tm\0";
			case 2075: return "159Tm\0";
			case 2076: return "160Tm\0";
			case 2077: return "161Tm\0";
			case 2078: return "162Tm\0";
			case 2079: return "163Tm\0";
			case 2080: return "164Tm\0";
			case 2081: return "165Tm\0";
			case 2082: return "166Tm\0";
			case 2083: return "167Tm\0";
			case 2084: return "168Tm\0";
			case 2085: return "169Tm\0";
			case 2086: return "170Tm\0";
			case 2087: return "171Tm\0";
			case 2088: return "172Tm\0";
			case 2089: return "173Tm\0";
			case 2090: return "174Tm\0";
			case 2091: return "175Tm\0";
			case 2092: return "176Tm\0";
			case 2093: return "177Tm\0";
			case 2094: return "178Tm\0";
			case 2095: return "179Tm\0";
			case 2096: return "148Yb\0";
			case 2097: return "149Yb\0";
			case 2098: return "150Yb\0";
			case 2099: return "151Yb\0";
			case 2100: return "152Yb\0";
			case 2101: return "153Yb\0";
			case 2102: return "154Yb\0";
			case 2103: return "155Yb\0";
			case 2104: return "156Yb\0";
			case 2105: return "157Yb\0";
			case 2106: return "158Yb\0";
			case 2107: return "159Yb\0";
			case 2108: return "160Yb\0";
			case 2109: return "161Yb\0";
			case 2110: return "162Yb\0";
			case 2111: return "163Yb\0";
			case 2112: return "164Yb\0";
			case 2113: return "165Yb\0";
			case 2114: return "166Yb\0";
			case 2115: return "167Yb\0";
			case 2116: return "168Yb\0";
			case 2117: return "169Yb\0";
			case 2118: return "170Yb\0";
			case 2119: return "171Yb\0";
			case 2120: return "172Yb\0";
			case 2121: return "173Yb\0";
			case 2122: return "174Yb\0";
			case 2123: return "175Yb\0";
			case 2124: return "176Yb\0";
			case 2125: return "177Yb\0";
			case 2126: return "178Yb\0";
			case 2127: return "179Yb\0";
			case 2128: return "180Yb\0";
			case 2129: return "181Yb\0";
			case 2130: return "150Lu\0";
			case 2131: return "151Lu\0";
			case 2132: return "152Lu\0";
			case 2133: return "153Lu\0";
			case 2134: return "154Lu\0";
			case 2135: return "155Lu\0";
			case 2136: return "156Lu\0";
			case 2137: return "157Lu\0";
			case 2138: return "158Lu\0";
			case 2139: return "159Lu\0";
			case 2140: return "160Lu\0";
			case 2141: return "161Lu\0";
			case 2142: return "162Lu\0";
			case 2143: return "163Lu\0";
			case 2144: return "164Lu\0";
			case 2145: return "165Lu\0";
			case 2146: return "166Lu\0";
			case 2147: return "167Lu\0";
			case 2148: return "168Lu\0";
			case 2149: return "169Lu\0";
			case 2150: return "170Lu\0";
			case 2151: return "171Lu\0";
			case 2152: return "172Lu\0";
			case 2153: return "173Lu\0";
			case 2154: return "174Lu\0";
			case 2155: return "175Lu\0";
			case 2156: return "176Lu\0";
			case 2157: return "177Lu\0";
			case 2158: return "178Lu\0";
			case 2159: return "179Lu\0";
			case 2160: return "180Lu\0";
			case 2161: return "181Lu\0";
			case 2162: return "182Lu\0";
			case 2163: return "183Lu\0";
			case 2164: return "184Lu\0";
			case 2165: return "185Lu\0";
			case 2166: return "153Hf\0";
			case 2167: return "154Hf\0";
			case 2168: return "155Hf\0";
			case 2169: return "156Hf\0";
			case 2170: return "157Hf\0";
			case 2171: return "158Hf\0";
			case 2172: return "159Hf\0";
			case 2173: return "160Hf\0";
			case 2174: return "161Hf\0";
			case 2175: return "162Hf\0";
			case 2176: return "163Hf\0";
			case 2177: return "164Hf\0";
			case 2178: return "165Hf\0";
			case 2179: return "166Hf\0";
			case 2180: return "167Hf\0";
			case 2181: return "168Hf\0";
			case 2182: return "169Hf\0";
			case 2183: return "170Hf\0";
			case 2184: return "171Hf\0";
			case 2185: return "172Hf\0";
			case 2186: return "173Hf\0";
			case 2187: return "174Hf\0";
			case 2188: return "175Hf\0";
			case 2189: return "176Hf\0";
			case 2190: return "177Hf\0";
			case 2191: return "178Hf\0";
			case 2192: return "179Hf\0";
			case 2193: return "180Hf\0";
			case 2194: return "181Hf\0";
			case 2195: return "182Hf\0";
			case 2196: return "183Hf\0";
			case 2197: return "184Hf\0";
			case 2198: return "185Hf\0";
			case 2199: return "186Hf\0";
			case 2200: return "187Hf\0";
			case 2201: return "188Hf\0";
			case 2202: return "189Hf\0";
			case 2203: return "155Ta\0";
			case 2204: return "156Ta\0";
			case 2205: return "157Ta\0";
			case 2206: return "158Ta\0";
			case 2207: return "159Ta\0";
			case 2208: return "160Ta\0";
			case 2209: return "161Ta\0";
			case 2210: return "162Ta\0";
			case 2211: return "163Ta\0";
			case 2212: return "164Ta\0";
			case 2213: return "165Ta\0";
			case 2214: return "166Ta\0";
			case 2215: return "167Ta\0";
			case 2216: return "168Ta\0";
			case 2217: return "169Ta\0";
			case 2218: return "170Ta\0";
			case 2219: return "171Ta\0";
			case 2220: return "172Ta\0";
			case 2221: return "173Ta\0";
			case 2222: return "174Ta\0";
			case 2223: return "175Ta\0";
			case 2224: return "176Ta\0";
			case 2225: return "177Ta\0";
			case 2226: return "178Ta\0";
			case 2227: return "179Ta\0";
			case 2228: return "180Ta\0";
			case 2229: return "181Ta\0";
			case 2230: return "182Ta\0";
			case 2231: return "183Ta\0";
			case 2232: return "184Ta\0";
			case 2233: return "185Ta\0";
			case 2234: return "186Ta\0";
			case 2235: return "187Ta\0";
			case 2236: return "188Ta\0";
			case 2237: return "189Ta\0";
			case 2238: return "190Ta\0";
			case 2239: return "191Ta\0";
			case 2240: return "192Ta\0";
			case 2241: return "157W\0";
			case 2242: return "158W\0";
			case 2243: return "159W\0";
			case 2244: return "160W\0";
			case 2245: return "161W\0";
			case 2246: return "162W\0";
			case 2247: return "163W\0";
			case 2248: return "164W\0";
			case 2249: return "165W\0";
			case 2250: return "166W\0";
			case 2251: return "167W\0";
			case 2252: return "168W\0";
			case 2253: return "169W\0";
			case 2254: return "170W\0";
			case 2255: return "171W\0";
			case 2256: return "172W\0";
			case 2257: return "173W\0";
			case 2258: return "174W\0";
			case 2259: return "175W\0";
			case 2260: return "176W\0";
			case 2261: return "177W\0";
			case 2262: return "178W\0";
			case 2263: return "179W\0";
			case 2264: return "180W\0";
			case 2265: return "181W\0";
			case 2266: return "182W\0";
			case 2267: return "183W\0";
			case 2268: return "184W\0";
			case 2269: return "185W\0";
			case 2270: return "186W\0";
			case 2271: return "187W\0";
			case 2272: return "188W\0";
			case 2273: return "189W\0";
			case 2274: return "190W\0";
			case 2275: return "191W\0";
			case 2276: return "192W\0";
			case 2277: return "193W\0";
			case 2278: return "194W\0";
			case 2279: return "159Re\0";
			case 2280: return "160Re\0";
			case 2281: return "161Re\0";
			case 2282: return "162Re\0";
			case 2283: return "163Re\0";
			case 2284: return "164Re\0";
			case 2285: return "165Re\0";
			case 2286: return "166Re\0";
			case 2287: return "167Re\0";
			case 2288: return "168Re\0";
			case 2289: return "169Re\0";
			case 2290: return "170Re\0";
			case 2291: return "171Re\0";
			case 2292: return "172Re\0";
			case 2293: return "173Re\0";
			case 2294: return "174Re\0";
			case 2295: return "175Re\0";
			case 2296: return "176Re\0";
			case 2297: return "177Re\0";
			case 2298: return "178Re\0";
			case 2299: return "179Re\0";
			case 2300: return "180Re\0";
			case 2301: return "181Re\0";
			case 2302: return "182Re\0";
			case 2303: return "183Re\0";
			case 2304: return "184Re\0";
			case 2305: return "185Re\0";
			case 2306: return "186Re\0";
			case 2307: return "187Re\0";
			case 2308: return "188Re\0";
			case 2309: return "189Re\0";
			case 2310: return "190Re\0";
			case 2311: return "191Re\0";
			case 2312: return "192Re\0";
			case 2313: return "193Re\0";
			case 2314: return "194Re\0";
			case 2315: return "195Re\0";
			case 2316: return "196Re\0";
			case 2317: return "197Re\0";
			case 2318: return "198Re\0";
			case 2319: return "161Os\0";
			case 2320: return "162Os\0";
			case 2321: return "163Os\0";
			case 2322: return "164Os\0";
			case 2323: return "165Os\0";
			case 2324: return "166Os\0";
			case 2325: return "167Os\0";
			case 2326: return "168Os\0";
			case 2327: return "169Os\0";
			case 2328: return "170Os\0";
			case 2329: return "171Os\0";
			case 2330: return "172Os\0";
			case 2331: return "173Os\0";
			case 2332: return "174Os\0";
			case 2333: return "175Os\0";
			case 2334: return "176Os\0";
			case 2335: return "177Os\0";
			case 2336: return "178Os\0";
			case 2337: return "179Os\0";
			case 2338: return "180Os\0";
			case 2339: return "181Os\0";
			case 2340: return "182Os\0";
			case 2341: return "183Os\0";
			case 2342: return "184Os\0";
			case 2343: return "185Os\0";
			case 2344: return "186Os\0";
			case 2345: return "187Os\0";
			case 2346: return "188Os\0";
			case 2347: return "189Os\0";
			case 2348: return "190Os\0";
			case 2349: return "191Os\0";
			case 2350: return "192Os\0";
			case 2351: return "193Os\0";
			case 2352: return "194Os\0";
			case 2353: return "195Os\0";
			case 2354: return "196Os\0";
			case 2355: return "197Os\0";
			case 2356: return "198Os\0";
			case 2357: return "199Os\0";
			case 2358: return "200Os\0";
			case 2359: return "201Os\0";
			case 2360: return "202Os\0";
			case 2361: return "164Ir\0";
			case 2362: return "165Ir\0";
			case 2363: return "166Ir\0";
			case 2364: return "167Ir\0";
			case 2365: return "168Ir\0";
			case 2366: return "169Ir\0";
			case 2367: return "170Ir\0";
			case 2368: return "171Ir\0";
			case 2369: return "172Ir\0";
			case 2370: return "173Ir\0";
			case 2371: return "174Ir\0";
			case 2372: return "175Ir\0";
			case 2373: return "176Ir\0";
			case 2374: return "177Ir\0";
			case 2375: return "178Ir\0";
			case 2376: return "179Ir\0";
			case 2377: return "180Ir\0";
			case 2378: return "181Ir\0";
			case 2379: return "182Ir\0";
			case 2380: return "183Ir\0";
			case 2381: return "184Ir\0";
			case 2382: return "185Ir\0";
			case 2383: return "186Ir\0";
			case 2384: return "187Ir\0";
			case 2385: return "188Ir\0";
			case 2386: return "189Ir\0";
			case 2387: return "190Ir\0";
			case 2388: return "191Ir\0";
			case 2389: return "192Ir\0";
			case 2390: return "193Ir\0";
			case 2391: return "194Ir\0";
			case 2392: return "195Ir\0";
			case 2393: return "196Ir\0";
			case 2394: return "197Ir\0";
			case 2395: return "198Ir\0";
			case 2396: return "199Ir\0";
			case 2397: return "200Ir\0";
			case 2398: return "201Ir\0";
			case 2399: return "202Ir\0";
			case 2400: return "203Ir\0";
			case 2401: return "204Ir\0";
			case 2402: return "166Pt\0";
			case 2403: return "167Pt\0";
			case 2404: return "168Pt\0";
			case 2405: return "169Pt\0";
			case 2406: return "170Pt\0";
			case 2407: return "171Pt\0";
			case 2408: return "172Pt\0";
			case 2409: return "173Pt\0";
			case 2410: return "174Pt\0";
			case 2411: return "175Pt\0";
			case 2412: return "176Pt\0";
			case 2413: return "177Pt\0";
			case 2414: return "178Pt\0";
			case 2415: return "179Pt\0";
			case 2416: return "180Pt\0";
			case 2417: return "181Pt\0";
			case 2418: return "182Pt\0";
			case 2419: return "183Pt\0";
			case 2420: return "184Pt\0";
			case 2421: return "185Pt\0";
			case 2422: return "186Pt\0";
			case 2423: return "187Pt\0";
			case 2424: return "188Pt\0";
			case 2425: return "189Pt\0";
			case 2426: return "190Pt\0";
			case 2427: return "191Pt\0";
			case 2428: return "192Pt\0";
			case 2429: return "193Pt\0";
			case 2430: return "194Pt\0";
			case 2431: return "195Pt\0";
			case 2432: return "196Pt\0";
			case 2433: return "197Pt\0";
			case 2434: return "198Pt\0";
			case 2435: return "199Pt\0";
			case 2436: return "200Pt\0";
			case 2437: return "201Pt\0";
			case 2438: return "202Pt\0";
			case 2439: return "203Pt\0";
			case 2440: return "204Pt\0";
			case 2441: return "205Pt\0";
			case 2442: return "206Pt\0";
			case 2443: return "169Au\0";
			case 2444: return "170Au\0";
			case 2445: return "171Au\0";
			case 2446: return "172Au\0";
			case 2447: return "173Au\0";
			case 2448: return "174Au\0";
			case 2449: return "175Au\0";
			case 2450: return "176Au\0";
			case 2451: return "177Au\0";
			case 2452: return "178Au\0";
			case 2453: return "179Au\0";
			case 2454: return "180Au\0";
			case 2455: return "181Au\0";
			case 2456: return "182Au\0";
			case 2457: return "183Au\0";
			case 2458: return "184Au\0";
			case 2459: return "185Au\0";
			case 2460: return "186Au\0";
			case 2461: return "187Au\0";
			case 2462: return "188Au\0";
			case 2463: return "189Au\0";
			case 2464: return "190Au\0";
			case 2465: return "191Au\0";
			case 2466: return "192Au\0";
			case 2467: return "193Au\0";
			case 2468: return "194Au\0";
			case 2469: return "195Au\0";
			case 2470: return "196Au\0";
			case 2471: return "197Au\0";
			case 2472: return "198Au\0";
			case 2473: return "199Au\0";
			case 2474: return "200Au\0";
			case 2475: return "201Au\0";
			case 2476: return "202Au\0";
			case 2477: return "203Au\0";
			case 2478: return "204Au\0";
			case 2479: return "205Au\0";
			case 2480: return "206Au\0";
			case 2481: return "207Au\0";
			case 2482: return "208Au\0";
			case 2483: return "209Au\0";
			case 2484: return "210Au\0";
			case 2485: return "171Hg\0";
			case 2486: return "172Hg\0";
			case 2487: return "173Hg\0";
			case 2488: return "174Hg\0";
			case 2489: return "175Hg\0";
			case 2490: return "176Hg\0";
			case 2491: return "177Hg\0";
			case 2492: return "178Hg\0";
			case 2493: return "179Hg\0";
			case 2494: return "180Hg\0";
			case 2495: return "181Hg\0";
			case 2496: return "182Hg\0";
			case 2497: return "183Hg\0";
			case 2498: return "184Hg\0";
			case 2499: return "185Hg\0";
			case 2500: return "186Hg\0";
			case 2501: return "187Hg\0";
			case 2502: return "188Hg\0";
			case 2503: return "189Hg\0";
			case 2504: return "190Hg\0";
			case 2505: return "191Hg\0";
			case 2506: return "192Hg\0";
			case 2507: return "193Hg\0";
			case 2508: return "194Hg\0";
			case 2509: return "195Hg\0";
			case 2510: return "196Hg\0";
			case 2511: return "197Hg\0";
			case 2512: return "198Hg\0";
			case 2513: return "199Hg\0";
			case 2514: return "200Hg\0";
			case 2515: return "201Hg\0";
			case 2516: return "202Hg\0";
			case 2517: return "203Hg\0";
			case 2518: return "204Hg\0";
			case 2519: return "205Hg\0";
			case 2520: return "206Hg\0";
			case 2521: return "207Hg\0";
			case 2522: return "208Hg\0";
			case 2523: return "209Hg\0";
			case 2524: return "210Hg\0";
			case 2525: return "211Hg\0";
			case 2526: return "212Hg\0";
			case 2527: return "213Hg\0";
			case 2528: return "214Hg\0";
			case 2529: return "215Hg\0";
			case 2530: return "216Hg\0";
			case 2531: return "176Tl\0";
			case 2532: return "177Tl\0";
			case 2533: return "178Tl\0";
			case 2534: return "179Tl\0";
			case 2535: return "180Tl\0";
			case 2536: return "181Tl\0";
			case 2537: return "182Tl\0";
			case 2538: return "183Tl\0";
			case 2539: return "184Tl\0";
			case 2540: return "185Tl\0";
			case 2541: return "186Tl\0";
			case 2542: return "187Tl\0";
			case 2543: return "188Tl\0";
			case 2544: return "189Tl\0";
			case 2545: return "190Tl\0";
			case 2546: return "191Tl\0";
			case 2547: return "192Tl\0";
			case 2548: return "193Tl\0";
			case 2549: return "194Tl\0";
			case 2550: return "195Tl\0";
			case 2551: return "196Tl\0";
			case 2552: return "197Tl\0";
			case 2553: return "198Tl\0";
			case 2554: return "199Tl\0";
			case 2555: return "200Tl\0";
			case 2556: return "201Tl\0";
			case 2557: return "202Tl\0";
			case 2558: return "203Tl\0";
			case 2559: return "204Tl\0";
			case 2560: return "205Tl\0";
			case 2561: return "206Tl\0";
			case 2562: return "207Tl\0";
			case 2563: return "208Tl\0";
			case 2564: return "209Tl\0";
			case 2565: return "210Tl\0";
			case 2566: return "211Tl\0";
			case 2567: return "212Tl\0";
			case 2568: return "213Tl\0";
			case 2569: return "214Tl\0";
			case 2570: return "215Tl\0";
			case 2571: return "216Tl\0";
			case 2572: return "217Tl\0";
			case 2573: return "218Tl\0";
			case 2574: return "178Pb\0";
			case 2575: return "179Pb\0";
			case 2576: return "180Pb\0";
			case 2577: return "181Pb\0";
			case 2578: return "182Pb\0";
			case 2579: return "183Pb\0";
			case 2580: return "184Pb\0";
			case 2581: return "185Pb\0";
			case 2582: return "186Pb\0";
			case 2583: return "187Pb\0";
			case 2584: return "188Pb\0";
			case 2585: return "189Pb\0";
			case 2586: return "190Pb\0";
			case 2587: return "191Pb\0";
			case 2588: return "192Pb\0";
			case 2589: return "193Pb\0";
			case 2590: return "194Pb\0";
			case 2591: return "195Pb\0";
			case 2592: return "196Pb\0";
			case 2593: return "197Pb\0";
			case 2594: return "198Pb\0";
			case 2595: return "199Pb\0";
			case 2596: return "200Pb\0";
			case 2597: return "201Pb\0";
			case 2598: return "202Pb\0";
			case 2599: return "203Pb\0";
			case 2600: return "204Pb\0";
			case 2601: return "205Pb\0";
			case 2602: return "206Pb\0";
			case 2603: return "207Pb\0";
			case 2604: return "208Pb\0";
			case 2605: return "209Pb\0";
			case 2606: return "210Pb\0";
			case 2607: return "211Pb\0";
			case 2608: return "212Pb\0";
			case 2609: return "213Pb\0";
			case 2610: return "214Pb\0";
			case 2611: return "215Pb\0";
			case 2612: return "216Pb\0";
			case 2613: return "217Pb\0";
			case 2614: return "218Pb\0";
			case 2615: return "219Pb\0";
			case 2616: return "220Pb\0";
			case 2617: return "184Bi\0";
			case 2618: return "185Bi\0";
			case 2619: return "186Bi\0";
			case 2620: return "187Bi\0";
			case 2621: return "188Bi\0";
			case 2622: return "189Bi\0";
			case 2623: return "190Bi\0";
			case 2624: return "191Bi\0";
			case 2625: return "192Bi\0";
			case 2626: return "193Bi\0";
			case 2627: return "194Bi\0";
			case 2628: return "195Bi\0";
			case 2629: return "196Bi\0";
			case 2630: return "197Bi\0";
			case 2631: return "198Bi\0";
			case 2632: return "199Bi\0";
			case 2633: return "200Bi\0";
			case 2634: return "201Bi\0";
			case 2635: return "202Bi\0";
			case 2636: return "203Bi\0";
			case 2637: return "204Bi\0";
			case 2638: return "205Bi\0";
			case 2639: return "206Bi\0";
			case 2640: return "207Bi\0";
			case 2641: return "208Bi\0";
			case 2642: return "209Bi\0";
			case 2643: return "210Bi\0";
			case 2644: return "211Bi\0";
			case 2645: return "212Bi\0";
			case 2646: return "213Bi\0";
			case 2647: return "214Bi\0";
			case 2648: return "215Bi\0";
			case 2649: return "216Bi\0";
			case 2650: return "217Bi\0";
			case 2651: return "218Bi\0";
			case 2652: return "219Bi\0";
			case 2653: return "220Bi\0";
			case 2654: return "221Bi\0";
			case 2655: return "222Bi\0";
			case 2656: return "223Bi\0";
			case 2657: return "224Bi\0";
			case 2658: return "186Po\0";
			case 2659: return "187Po\0";
			case 2660: return "188Po\0";
			case 2661: return "189Po\0";
			case 2662: return "190Po\0";
			case 2663: return "191Po\0";
			case 2664: return "192Po\0";
			case 2665: return "193Po\0";
			case 2666: return "194Po\0";
			case 2667: return "195Po\0";
			case 2668: return "196Po\0";
			case 2669: return "197Po\0";
			case 2670: return "198Po\0";
			case 2671: return "199Po\0";
			case 2672: return "200Po\0";
			case 2673: return "201Po\0";
			case 2674: return "202Po\0";
			case 2675: return "203Po\0";
			case 2676: return "204Po\0";
			case 2677: return "205Po\0";
			case 2678: return "206Po\0";
			case 2679: return "207Po\0";
			case 2680: return "208Po\0";
			case 2681: return "209Po\0";
			case 2682: return "210Po\0";
			case 2683: return "211Po\0";
			case 2684: return "212Po\0";
			case 2685: return "213Po\0";
			case 2686: return "214Po\0";
			case 2687: return "215Po\0";
			case 2688: return "216Po\0";
			case 2689: return "217Po\0";
			case 2690: return "218Po\0";
			case 2691: return "219Po\0";
			case 2692: return "220Po\0";
			case 2693: return "221Po\0";
			case 2694: return "222Po\0";
			case 2695: return "223Po\0";
			case 2696: return "224Po\0";
			case 2697: return "225Po\0";
			case 2698: return "226Po\0";
			case 2699: return "227Po\0";
			case 2700: return "191At\0";
			case 2701: return "192At\0";
			case 2702: return "193At\0";
			case 2703: return "194At\0";
			case 2704: return "195At\0";
			case 2705: return "196At\0";
			case 2706: return "197At\0";
			case 2707: return "198At\0";
			case 2708: return "199At\0";
			case 2709: return "200At\0";
			case 2710: return "201At\0";
			case 2711: return "202At\0";
			case 2712: return "203At\0";
			case 2713: return "204At\0";
			case 2714: return "205At\0";
			case 2715: return "206At\0";
			case 2716: return "207At\0";
			case 2717: return "208At\0";
			case 2718: return "209At\0";
			case 2719: return "210At\0";
			case 2720: return "211At\0";
			case 2721: return "212At\0";
			case 2722: return "213At\0";
			case 2723: return "214At\0";
			case 2724: return "215At\0";
			case 2725: return "216At\0";
			case 2726: return "217At\0";
			case 2727: return "218At\0";
			case 2728: return "219At\0";
			case 2729: return "220At\0";
			case 2730: return "221At\0";
			case 2731: return "222At\0";
			case 2732: return "223At\0";
			case 2733: return "224At\0";
			case 2734: return "225At\0";
			case 2735: return "226At\0";
			case 2736: return "227At\0";
			case 2737: return "228At\0";
			case 2738: return "229At\0";
			case 2739: return "193Rn\0";
			case 2740: return "194Rn\0";
			case 2741: return "195Rn\0";
			case 2742: return "196Rn\0";
			case 2743: return "197Rn\0";
			case 2744: return "198Rn\0";
			case 2745: return "199Rn\0";
			case 2746: return "200Rn\0";
			case 2747: return "201Rn\0";
			case 2748: return "202Rn\0";
			case 2749: return "203Rn\0";
			case 2750: return "204Rn\0";
			case 2751: return "205Rn\0";
			case 2752: return "206Rn\0";
			case 2753: return "207Rn\0";
			case 2754: return "208Rn\0";
			case 2755: return "209Rn\0";
			case 2756: return "210Rn\0";
			case 2757: return "211Rn\0";
			case 2758: return "212Rn\0";
			case 2759: return "213Rn\0";
			case 2760: return "214Rn\0";
			case 2761: return "215Rn\0";
			case 2762: return "216Rn\0";
			case 2763: return "217Rn\0";
			case 2764: return "218Rn\0";
			case 2765: return "219Rn\0";
			case 2766: return "220Rn\0";
			case 2767: return "221Rn\0";
			case 2768: return "222Rn\0";
			case 2769: return "223Rn\0";
			case 2770: return "224Rn\0";
			case 2771: return "225Rn\0";
			case 2772: return "226Rn\0";
			case 2773: return "227Rn\0";
			case 2774: return "228Rn\0";
			case 2775: return "229Rn\0";
			case 2776: return "230Rn\0";
			case 2777: return "231Rn\0";
			case 2778: return "199Fr\0";
			case 2779: return "200Fr\0";
			case 2780: return "201Fr\0";
			case 2781: return "202Fr\0";
			case 2782: return "203Fr\0";
			case 2783: return "204Fr\0";
			case 2784: return "205Fr\0";
			case 2785: return "206Fr\0";
			case 2786: return "207Fr\0";
			case 2787: return "208Fr\0";
			case 2788: return "209Fr\0";
			case 2789: return "210Fr\0";
			case 2790: return "211Fr\0";
			case 2791: return "212Fr\0";
			case 2792: return "213Fr\0";
			case 2793: return "214Fr\0";
			case 2794: return "215Fr\0";
			case 2795: return "216Fr\0";
			case 2796: return "217Fr\0";
			case 2797: return "218Fr\0";
			case 2798: return "219Fr\0";
			case 2799: return "220Fr\0";
			case 2800: return "221Fr\0";
			case 2801: return "222Fr\0";
			case 2802: return "223Fr\0";
			case 2803: return "224Fr\0";
			case 2804: return "225Fr\0";
			case 2805: return "226Fr\0";
			case 2806: return "227Fr\0";
			case 2807: return "228Fr\0";
			case 2808: return "229Fr\0";
			case 2809: return "230Fr\0";
			case 2810: return "231Fr\0";
			case 2811: return "232Fr\0";
			case 2812: return "233Fr\0";
			case 2813: return "201Ra\0";
			case 2814: return "202Ra\0";
			case 2815: return "203Ra\0";
			case 2816: return "204Ra\0";
			case 2817: return "205Ra\0";
			case 2818: return "206Ra\0";
			case 2819: return "207Ra\0";
			case 2820: return "208Ra\0";
			case 2821: return "209Ra\0";
			case 2822: return "210Ra\0";
			case 2823: return "211Ra\0";
			case 2824: return "212Ra\0";
			case 2825: return "213Ra\0";
			case 2826: return "214Ra\0";
			case 2827: return "215Ra\0";
			case 2828: return "216Ra\0";
			case 2829: return "217Ra\0";
			case 2830: return "218Ra\0";
			case 2831: return "219Ra\0";
			case 2832: return "220Ra\0";
			case 2833: return "221Ra\0";
			case 2834: return "222Ra\0";
			case 2835: return "223Ra\0";
			case 2836: return "224Ra\0";
			case 2837: return "225Ra\0";
			case 2838: return "226Ra\0";
			case 2839: return "227Ra\0";
			case 2840: return "228Ra\0";
			case 2841: return "229Ra\0";
			case 2842: return "230Ra\0";
			case 2843: return "231Ra\0";
			case 2844: return "232Ra\0";
			case 2845: return "233Ra\0";
			case 2846: return "234Ra\0";
			case 2847: return "235Ra\0";
			case 2848: return "206Ac\0";
			case 2849: return "207Ac\0";
			case 2850: return "208Ac\0";
			case 2851: return "209Ac\0";
			case 2852: return "210Ac\0";
			case 2853: return "211Ac\0";
			case 2854: return "212Ac\0";
			case 2855: return "213Ac\0";
			case 2856: return "214Ac\0";
			case 2857: return "215Ac\0";
			case 2858: return "216Ac\0";
			case 2859: return "217Ac\0";
			case 2860: return "218Ac\0";
			case 2861: return "219Ac\0";
			case 2862: return "220Ac\0";
			case 2863: return "221Ac\0";
			case 2864: return "222Ac\0";
			case 2865: return "223Ac\0";
			case 2866: return "224Ac\0";
			case 2867: return "225Ac\0";
			case 2868: return "226Ac\0";
			case 2869: return "227Ac\0";
			case 2870: return "228Ac\0";
			case 2871: return "229Ac\0";
			case 2872: return "230Ac\0";
			case 2873: return "231Ac\0";
			case 2874: return "232Ac\0";
			case 2875: return "233Ac\0";
			case 2876: return "234Ac\0";
			case 2877: return "235Ac\0";
			case 2878: return "236Ac\0";
			case 2879: return "237Ac\0";
			case 2880: return "208Th\0";
			case 2881: return "209Th\0";
			case 2882: return "210Th\0";
			case 2883: return "211Th\0";
			case 2884: return "212Th\0";
			case 2885: return "213Th\0";
			case 2886: return "214Th\0";
			case 2887: return "215Th\0";
			case 2888: return "216Th\0";
			case 2889: return "217Th\0";
			case 2890: return "218Th\0";
			case 2891: return "219Th\0";
			case 2892: return "220Th\0";
			case 2893: return "221Th\0";
			case 2894: return "222Th\0";
			case 2895: return "223Th\0";
			case 2896: return "224Th\0";
			case 2897: return "225Th\0";
			case 2898: return "226Th\0";
			case 2899: return "227Th\0";
			case 2900: return "228Th\0";
			case 2901: return "229Th\0";
			case 2902: return "230Th\0";
			case 2903: return "231Th\0";
			case 2904: return "232Th\0";
			case 2905: return "233Th\0";
			case 2906: return "234Th\0";
			case 2907: return "235Th\0";
			case 2908: return "236Th\0";
			case 2909: return "237Th\0";
			case 2910: return "238Th\0";
			case 2911: return "239Th\0";
			case 2912: return "212Pa\0";
			case 2913: return "213Pa\0";
			case 2914: return "214Pa\0";
			case 2915: return "215Pa\0";
			case 2916: return "216Pa\0";
			case 2917: return "217Pa\0";
			case 2918: return "218Pa\0";
			case 2919: return "219Pa\0";
			case 2920: return "220Pa\0";
			case 2921: return "221Pa\0";
			case 2922: return "222Pa\0";
			case 2923: return "223Pa\0";
			case 2924: return "224Pa\0";
			case 2925: return "225Pa\0";
			case 2926: return "226Pa\0";
			case 2927: return "227Pa\0";
			case 2928: return "228Pa\0";
			case 2929: return "229Pa\0";
			case 2930: return "230Pa\0";
			case 2931: return "231Pa\0";
			case 2932: return "232Pa\0";
			case 2933: return "233Pa\0";
			case 2934: return "234Pa\0";
			case 2935: return "235Pa\0";
			case 2936: return "236Pa\0";
			case 2937: return "237Pa\0";
			case 2938: return "238Pa\0";
			case 2939: return "239Pa\0";
			case 2940: return "240Pa\0";
			case 2941: return "241Pa\0";
			case 2942: return "217U\0";
			case 2943: return "218U\0";
			case 2944: return "219U\0";
			case 2945: return "220U\0";
			case 2946: return "221U\0";
			case 2947: return "222U\0";
			case 2948: return "223U\0";
			case 2949: return "224U\0";
			case 2950: return "225U\0";
			case 2951: return "226U\0";
			case 2952: return "227U\0";
			case 2953: return "228U\0";
			case 2954: return "229U\0";
			case 2955: return "230U\0";
			case 2956: return "231U\0";
			case 2957: return "232U\0";
			case 2958: return "233U\0";
			case 2959: return "234U\0";
			case 2960: return "235U\0";
			case 2961: return "236U\0";
			case 2962: return "237U\0";
			case 2963: return "238U\0";
			case 2964: return "239U\0";
			case 2965: return "240U\0";
			case 2966: return "241U\0";
			case 2967: return "242U\0";
			case 2968: return "243U\0";
			case 2969: return "219Np\0";
			case 2970: return "220Np\0";
			case 2971: return "221Np\0";
			case 2972: return "222Np\0";
			case 2973: return "223Np\0";
			case 2974: return "224Np\0";
			case 2975: return "225Np\0";
			case 2976: return "226Np\0";
			case 2977: return "227Np\0";
			case 2978: return "228Np\0";
			case 2979: return "229Np\0";
			case 2980: return "230Np\0";
			case 2981: return "231Np\0";
			case 2982: return "232Np\0";
			case 2983: return "233Np\0";
			case 2984: return "234Np\0";
			case 2985: return "235Np\0";
			case 2986: return "236Np\0";
			case 2987: return "237Np\0";
			case 2988: return "238Np\0";
			case 2989: return "239Np\0";
			case 2990: return "240Np\0";
			case 2991: return "241Np\0";
			case 2992: return "242Np\0";
			case 2993: return "243Np\0";
			case 2994: return "244Np\0";
			case 2995: return "245Np\0";
			case 2996: return "228Pu\0";
			case 2997: return "229Pu\0";
			case 2998: return "230Pu\0";
			case 2999: return "231Pu\0";
			case 3000: return "232Pu\0";
			case 3001: return "233Pu\0";
			case 3002: return "234Pu\0";
			case 3003: return "235Pu\0";
			case 3004: return "236Pu\0";
			case 3005: return "237Pu\0";
			case 3006: return "238Pu\0";
			case 3007: return "239Pu\0";
			case 3008: return "240Pu\0";
			case 3009: return "241Pu\0";
			case 3010: return "242Pu\0";
			case 3011: return "243Pu\0";
			case 3012: return "244Pu\0";
			case 3013: return "245Pu\0";
			case 3014: return "246Pu\0";
			case 3015: return "247Pu\0";
			case 3016: return "230Am\0";
			case 3017: return "231Am\0";
			case 3018: return "232Am\0";
			case 3019: return "233Am\0";
			case 3020: return "234Am\0";
			case 3021: return "235Am\0";
			case 3022: return "236Am\0";
			case 3023: return "237Am\0";
			case 3024: return "238Am\0";
			case 3025: return "239Am\0";
			case 3026: return "240Am\0";
			case 3027: return "241Am\0";
			case 3028: return "242Am\0";
			case 3029: return "243Am\0";
			case 3030: return "244Am\0";
			case 3031: return "245Am\0";
			case 3032: return "246Am\0";
			case 3033: return "247Am\0";
			case 3034: return "248Am\0";
			case 3035: return "249Am\0";
			case 3036: return "232Cm\0";
			case 3037: return "233Cm\0";
			case 3038: return "234Cm\0";
			case 3039: return "235Cm\0";
			case 3040: return "236Cm\0";
			case 3041: return "237Cm\0";
			case 3042: return "238Cm\0";
			case 3043: return "239Cm\0";
			case 3044: return "240Cm\0";
			case 3045: return "241Cm\0";
			case 3046: return "242Cm\0";
			case 3047: return "243Cm\0";
			case 3048: return "244Cm\0";
			case 3049: return "245Cm\0";
			case 3050: return "246Cm\0";
			case 3051: return "247Cm\0";
			case 3052: return "248Cm\0";
			case 3053: return "249Cm\0";
			case 3054: return "250Cm\0";
			case 3055: return "251Cm\0";
			case 3056: return "252Cm\0";
			case 3057: return "234Bk\0";
			case 3058: return "235Bk\0";
			case 3059: return "236Bk\0";
			case 3060: return "237Bk\0";
			case 3061: return "238Bk\0";
			case 3062: return "239Bk\0";
			case 3063: return "240Bk\0";
			case 3064: return "241Bk\0";
			case 3065: return "242Bk\0";
			case 3066: return "243Bk\0";
			case 3067: return "244Bk\0";
			case 3068: return "245Bk\0";
			case 3069: return "246Bk\0";
			case 3070: return "247Bk\0";
			case 3071: return "248Bk\0";
			case 3072: return "249Bk\0";
			case 3073: return "250Bk\0";
			case 3074: return "251Bk\0";
			case 3075: return "252Bk\0";
			case 3076: return "253Bk\0";
			case 3077: return "254Bk\0";
			case 3078: return "237Cf\0";
			case 3079: return "238Cf\0";
			case 3080: return "239Cf\0";
			case 3081: return "240Cf\0";
			case 3082: return "241Cf\0";
			case 3083: return "242Cf\0";
			case 3084: return "243Cf\0";
			case 3085: return "244Cf\0";
			case 3086: return "245Cf\0";
			case 3087: return "246Cf\0";
			case 3088: return "247Cf\0";
			case 3089: return "248Cf\0";
			case 3090: return "249Cf\0";
			case 3091: return "250Cf\0";
			case 3092: return "251Cf\0";
			case 3093: return "252Cf\0";
			case 3094: return "253Cf\0";
			case 3095: return "254Cf\0";
			case 3096: return "255Cf\0";
			case 3097: return "256Cf\0";
			case 3098: return "239Es\0";
			case 3099: return "240Es\0";
			case 3100: return "241Es\0";
			case 3101: return "242Es\0";
			case 3102: return "243Es\0";
			case 3103: return "244Es\0";
			case 3104: return "245Es\0";
			case 3105: return "246Es\0";
			case 3106: return "247Es\0";
			case 3107: return "248Es\0";
			case 3108: return "249Es\0";
			case 3109: return "250Es\0";
			case 3110: return "251Es\0";
			case 3111: return "252Es\0";
			case 3112: return "253Es\0";
			case 3113: return "254Es\0";
			case 3114: return "255Es\0";
			case 3115: return "256Es\0";
			case 3116: return "257Es\0";
			case 3117: return "258Es\0";
			case 3118: return "241Fm\0";
			case 3119: return "242Fm\0";
			case 3120: return "243Fm\0";
			case 3121: return "244Fm\0";
			case 3122: return "245Fm\0";
			case 3123: return "246Fm\0";
			case 3124: return "247Fm\0";
			case 3125: return "248Fm\0";
			case 3126: return "249Fm\0";
			case 3127: return "250Fm\0";
			case 3128: return "251Fm\0";
			case 3129: return "252Fm\0";
			case 3130: return "253Fm\0";
			case 3131: return "254Fm\0";
			case 3132: return "255Fm\0";
			case 3133: return "256Fm\0";
			case 3134: return "257Fm\0";
			case 3135: return "258Fm\0";
			case 3136: return "259Fm\0";
			case 3137: return "260Fm\0";
			case 3138: return "245Md\0";
			case 3139: return "246Md\0";
			case 3140: return "247Md\0";
			case 3141: return "248Md\0";
			case 3142: return "249Md\0";
			case 3143: return "250Md\0";
			case 3144: return "251Md\0";
			case 3145: return "252Md\0";
			case 3146: return "253Md\0";
			case 3147: return "254Md\0";
			case 3148: return "255Md\0";
			case 3149: return "256Md\0";
			case 3150: return "257Md\0";
			case 3151: return "258Md\0";
			case 3152: return "259Md\0";
			case 3153: return "260Md\0";
			case 3154: return "261Md\0";
			case 3155: return "262Md\0";
			case 3156: return "248No\0";
			case 3157: return "249No\0";
			case 3158: return "250No\0";
			case 3159: return "251No\0";
			case 3160: return "252No\0";
			case 3161: return "253No\0";
			case 3162: return "254No\0";
			case 3163: return "255No\0";
			case 3164: return "256No\0";
			case 3165: return "257No\0";
			case 3166: return "258No\0";
			case 3167: return "259No\0";
			case 3168: return "260No\0";
			case 3169: return "261No\0";
			case 3170: return "262No\0";
			case 3171: return "263No\0";
			case 3172: return "264No\0";
			case 3173: return "251Lr\0";
			case 3174: return "252Lr\0";
			case 3175: return "253Lr\0";
			case 3176: return "254Lr\0";
			case 3177: return "255Lr\0";
			case 3178: return "256Lr\0";
			case 3179: return "257Lr\0";
			case 3180: return "258Lr\0";
			case 3181: return "259Lr\0";
			case 3182: return "260Lr\0";
			case 3183: return "261Lr\0";
			case 3184: return "262Lr\0";
			case 3185: return "263Lr\0";
			case 3186: return "264Lr\0";
			case 3187: return "265Lr\0";
			case 3188: return "266Lr\0";
			case 3189: return "253Rf\0";
			case 3190: return "254Rf\0";
			case 3191: return "255Rf\0";
			case 3192: return "256Rf\0";
			case 3193: return "257Rf\0";
			case 3194: return "258Rf\0";
			case 3195: return "259Rf\0";
			case 3196: return "260Rf\0";
			case 3197: return "261Rf\0";
			case 3198: return "262Rf\0";
			case 3199: return "263Rf\0";
			case 3200: return "264Rf\0";
			case 3201: return "265Rf\0";
			case 3202: return "266Rf\0";
			case 3203: return "267Rf\0";
			case 3204: return "268Rf\0";
			case 3205: return "255Db\0";
			case 3206: return "256Db\0";
			case 3207: return "257Db\0";
			case 3208: return "258Db\0";
			case 3209: return "259Db\0";
			case 3210: return "260Db\0";
			case 3211: return "261Db\0";
			case 3212: return "262Db\0";
			case 3213: return "263Db\0";
			case 3214: return "264Db\0";
			case 3215: return "265Db\0";
			case 3216: return "266Db\0";
			case 3217: return "267Db\0";
			case 3218: return "268Db\0";
			case 3219: return "269Db\0";
			case 3220: return "270Db\0";
			case 3221: return "258Sg\0";
			case 3222: return "259Sg\0";
			case 3223: return "260Sg\0";
			case 3224: return "261Sg\0";
			case 3225: return "262Sg\0";
			case 3226: return "263Sg\0";
			case 3227: return "264Sg\0";
			case 3228: return "265Sg\0";
			case 3229: return "266Sg\0";
			case 3230: return "267Sg\0";
			case 3231: return "268Sg\0";
			case 3232: return "269Sg\0";
			case 3233: return "270Sg\0";
			case 3234: return "271Sg\0";
			case 3235: return "272Sg\0";
			case 3236: return "273Sg\0";
			case 3237: return "260Bh\0";
			case 3238: return "261Bh\0";
			case 3239: return "262Bh\0";
			case 3240: return "263Bh\0";
			case 3241: return "264Bh\0";
			case 3242: return "265Bh\0";
			case 3243: return "266Bh\0";
			case 3244: return "267Bh\0";
			case 3245: return "268Bh\0";
			case 3246: return "269Bh\0";
			case 3247: return "270Bh\0";
			case 3248: return "271Bh\0";
			case 3249: return "272Bh\0";
			case 3250: return "273Bh\0";
			case 3251: return "274Bh\0";
			case 3252: return "275Bh\0";
			case 3253: return "263Hs\0";
			case 3254: return "264Hs\0";
			case 3255: return "265Hs\0";
			case 3256: return "266Hs\0";
			case 3257: return "267Hs\0";
			case 3258: return "268Hs\0";
			case 3259: return "269Hs\0";
			case 3260: return "270Hs\0";
			case 3261: return "271Hs\0";
			case 3262: return "272Hs\0";
			case 3263: return "273Hs\0";
			case 3264: return "274Hs\0";
			case 3265: return "275Hs\0";
			case 3266: return "276Hs\0";
			case 3267: return "277Hs\0";
			case 3268: return "265Mt\0";
			case 3269: return "266Mt\0";
			case 3270: return "267Mt\0";
			case 3271: return "268Mt\0";
			case 3272: return "269Mt\0";
			case 3273: return "270Mt\0";
			case 3274: return "271Mt\0";
			case 3275: return "272Mt\0";
			case 3276: return "273Mt\0";
			case 3277: return "274Mt\0";
			case 3278: return "275Mt\0";
			case 3279: return "276Mt\0";
			case 3280: return "277Mt\0";
			case 3281: return "278Mt\0";
			case 3282: return "279Mt\0";
			case 3283: return "267Ds\0";
			case 3284: return "268Ds\0";
			case 3285: return "269Ds\0";
			case 3286: return "270Ds\0";
			case 3287: return "271Ds\0";
			case 3288: return "272Ds\0";
			case 3289: return "273Ds\0";
			case 3290: return "274Ds\0";
			case 3291: return "275Ds\0";
			case 3292: return "276Ds\0";
			case 3293: return "277Ds\0";
			case 3294: return "278Ds\0";
			case 3295: return "279Ds\0";
			case 3296: return "280Ds\0";
			case 3297: return "281Ds\0";
			case 3298: return "272Rg\0";
			case 3299: return "273Rg\0";
			case 3300: return "274Rg\0";
			case 3301: return "275Rg\0";
			case 3302: return "276Rg\0";
			case 3303: return "277Rg\0";
			case 3304: return "278Rg\0";
			case 3305: return "279Rg\0";
			case 3306: return "280Rg\0";
			case 3307: return "281Rg\0";
			case 3308: return "282Rg\0";
			case 3309: return "283Rg\0";
			case 3310: return "276Cn\0";
			case 3311: return "277Cn\0";
			case 3312: return "278Cn\0";
			case 3313: return "279Cn\0";
			case 3314: return "280Cn\0";
			case 3315: return "281Cn\0";
			case 3316: return "282Cn\0";
			case 3317: return "283Cn\0";
			case 3318: return "284Cn\0";
			case 3319: return "285Cn\0";
			case 3320: return "278Nh\0";
			case 3321: return "279Nh\0";
			case 3322: return "280Nh\0";
			case 3323: return "281Nh\0";
			case 3324: return "282Nh\0";
			case 3325: return "283Nh\0";
			case 3326: return "284Nh\0";
			case 3327: return "285Nh\0";
			case 3328: return "286Nh\0";
			case 3329: return "287Nh\0";
			case 3330: return "285Fl\0";
			case 3331: return "286Fl\0";
			case 3332: return "287Fl\0";
			case 3333: return "288Fl\0";
			case 3334: return "289Fl\0";
			case 3335: return "287Mc\0";
			case 3336: return "288Mc\0";
			case 3337: return "289Mc\0";
			case 3338: return "290Mc\0";
			case 3339: return "291Uup\0";
			case 3340: return "289Lv\0";
			case 3341: return "290Lv\0";
			case 3342: return "291Lv\0";
			case 3343: return "292Lv\0";
			case 3344: return "293Lv\0";
			case 3345: return "291Ts\0";
			case 3346: return "292Ts\0";
			case 3347: return "293Ts\0";
			case 3348: return "294Uus\0";
			case 3349: return "293Og\0";
			case 3350: return "294Og\0";
			case 3351: return "295Og\0";
			  default: return "\0";
		}
	}

	static nist::Isotope isotope_enum(c_str symbol)
	{
		for (mut<usize> n = 0; n < nist::MAX_ISOTOPE_COUNT; ++n) {
			auto result = static_cast<nist::Isotope>(n);

			auto found = std::strcmp(nist::atomic_symbol(result), symbol) == 0;

			if (found) {
				return result;
			}
		}

		print::error(WHERE, "Invalid atomic symbol ", symbol);

		// NOTE: Unreachable.
		return nist::Isotope::atom_unknown;
	}

	static constexpr f64 atomic_mass(const nist::Isotope a)
	{
		switch (as_u16(a)) {
			case    0: return 1.007825032239;   // 1H
			case    1: return 2.0141017781212;  // 2H
			case    2: return 3.016049277924;   // 3H
			case    3: return 4.0264311;        // 4H
			case    4: return 5.03531196;       // 5H
			case    5: return 6.0449627;        // 6H
			case    6: return 7.052711;         // 7H
			case    7: return 3.016029320125;   // 3He
			case    8: return 4.002603254136;   // 4He
			case    9: return 5.01205721;       // 5He
			case   10: return 6.01888589157;    // 6He
			case   11: return 7.027990781;      // 7He
			case   12: return 8.03393439095;    // 8He
			case   13: return 9.04394650;       // 9He
			case   14: return 10.0527911;       // 10He
			case   15: return 3.030821;         // 3Li
			case   16: return 4.0271923;        // 4Li
			case   17: return 5.01253854;       // 5Li
			case   18: return 6.015122887416;   // 6Li
			case   19: return 7.016003436645;   // 7Li
			case   20: return 8.02248624650;    // 8Li
			case   21: return 9.0267901920;     // 9Li
			case   22: return 10.03548314;      // 10Li
			case   23: return 11.0437235866;    // 11Li
			case   24: return 12.05251716;      // 12Li
			case   25: return 13.0626338;       // 13Li
			case   26: return 5.039922;         // 5Be
			case   27: return 6.019726458;      // 6Be
			case   28: return 7.01692871776;    // 7Be
			case   29: return 8.00530510237;    // 8Be
			case   30: return 9.01218306582;    // 9Be
			case   31: return 10.01353469586;   // 10Be
			case   32: return 11.0216610826;    // 11Be
			case   33: return 12.026922120;     // 12Be
			case   34: return 13.03613511;      // 13Be
			case   35: return 14.0428914;       // 14Be
			case   36: return 15.0534243;       // 15Be
			case   37: return 16.0616718;       // 16Be
			case   38: return 6.050822;         // 6B
			case   39: return 7.02971227;       // 7B
			case   40: return 8.024607311;      // 8B
			case   41: return 9.0133296597;     // 9B
			case   42: return 10.0129369541;    // 10B
			case   43: return 11.0093053645;    // 11B
			case   44: return 12.014352714;     // 12B
			case   45: return 13.017780212;     // 13B
			case   46: return 14.02540423;      // 14B
			case   47: return 15.03108823;      // 15B
			case   48: return 16.03984226;      // 16B
			case   49: return 17.0469918;       // 17B
			case   50: return 18.0556618;       // 18B
			case   51: return 19.0631043;       // 19B
			case   52: return 20.0720775;       // 20B
			case   53: return 21.0812997;       // 21B
			case   54: return 8.03764320;       // 8C
			case   55: return 9.031037223;      // 9C
			case   56: return 10.0168533142;    // 10C
			case   57: return 11.011433610;     // 11C
			case   58: return 12.000000000;     // 12C
			case   59: return 13.0033548350723; // 13C
			case   60: return 14.003241988440;  // 14C
			case   61: return 15.0105992686;    // 15C
			case   62: return 16.014701338;     // 16C
			case   63: return 17.02257719;      // 17C
			case   64: return 18.02675132;      // 18C
			case   65: return 19.0348011;       // 19C
			case   66: return 20.0403226;       // 20C
			case   67: return 21.0490043;       // 21C
			case   68: return 22.0575326;       // 22C
			case   69: return 23.068911;        // 23C
			case   70: return 10.0416543;       // 10N
			case   71: return 11.02609150;      // 11N
			case   72: return 12.018613211;     // 12N
			case   73: return 13.0057386129;    // 13N
			case   74: return 14.0030740044320; // 14N
			case   75: return 15.0001088988864; // 15N
			case   76: return 16.006101925;     // 16N
			case   77: return 17.00844916;      // 17N
			case   78: return 18.01407820;      // 18N
			case   79: return 19.01702218;      // 19N
			case   80: return 20.02336660;      // 20N
			case   81: return 21.0271110;       // 21N
			case   82: return 22.0343921;       // 22N
			case   83: return 23.0411432;       // 23N
			case   84: return 24.0503943;       // 24N
			case   85: return 25.0601054;       // 25N
			case   86: return 12.03426226;      // 12O
			case   87: return 13.02481510;      // 13O
			case   88: return 14.0085963612;    // 14O
			case   89: return 15.0030656253;    // 15O
			case   90: return 15.9949146195717; // 16O
			case   91: return 16.9991317565069; // 17O
			case   92: return 17.9991596128676; // 18O
			case   93: return 19.003578028;     // 19O
			case   94: return 20.0040753595;    // 20O
			case   95: return 21.00865513;      // 21O
			case   96: return 22.00996661;      // 22O
			case   97: return 23.01569697;      // 23O
			case   98: return 24.0198612;       // 24O
			case   99: return 25.0293612;       // 25O
			case  100: return 26.0372917;       // 26O
			case  101: return 27.0477254;       // 27O
			case  102: return 28.0559175;       // 28O
			case  103: return 14.03431544;      // 14F
			case  104: return 15.01804367;      // 15F
			case  105: return 16.011465789;     // 16F
			case  106: return 17.0020952427;    // 17F
			case  107: return 18.0009373350;    // 18F
			case  108: return 18.9984031627392; // 19F
			case  109: return 19.99998125231;   // 20F
			case  110: return 20.999948919;     // 21F
			case  111: return 22.00299913;      // 22F
			case  112: return 23.00355754;      // 23F
			case  113: return 24.00811578;      // 24F
			case  114: return 25.01219981;      // 25F
			case  115: return 26.02003883;      // 26F
			case  116: return 27.0264420;       // 27F
			case  117: return 28.0353421;       // 28F
			case  118: return 29.0425454;       // 29F
			case  119: return 30.0516564;       // 30F
			case  120: return 31.0597156;       // 31F
			case  121: return 16.02575022;      // 16Ne
			case  122: return 17.0177139638;    // 17Ne
			case  123: return 18.0057087039;    // 18Ne
			case  124: return 19.0018809117;    // 19Ne
			case  125: return 19.992440176217;  // 20Ne
			case  126: return 20.99384668541;   // 21Ne
			case  127: return 21.99138511418;   // 22Ne
			case  128: return 22.9944669111;    // 23Ne
			case  129: return 23.9936106555;    // 24Ne
			case  130: return 24.99778948;      // 25Ne
			case  131: return 26.00051520;      // 26Ne
			case  132: return 27.00755370;      // 27Ne
			case  133: return 28.0121210;       // 28Ne
			case  134: return 29.0197511;       // 29Ne
			case  135: return 30.0247330;       // 30Ne
			case  136: return 31.033117;        // 31Ne
			case  137: return 32.0397254;       // 32Ne
			case  138: return 33.0493864;       // 33Ne
			case  139: return 34.0567355;       // 34Ne
			case  140: return 18.0268812;       // 18Na
			case  141: return 19.01388011;      // 19Na
			case  142: return 20.007354412;     // 20Na
			case  143: return 20.9976546930;    // 21Na
			case  144: return 21.9944374118;    // 22Na
			case  145: return 22.989769282019;  // 23Na
			case  146: return 23.99096295038;   // 24Na
			case  147: return 24.989954013;     // 25Na
			case  148: return 25.992634638;     // 26Na
			case  149: return 26.994076540;     // 27Na
			case  150: return 27.99893911;      // 28Na
			case  151: return 29.002877179;     // 29Na
			case  152: return 30.009097951;     // 30Na
			case  153: return 31.01316325;      // 31Na
			case  154: return 32.0201913;       // 32Na
			case  155: return 33.0257364;       // 33Na
			case  156: return 34.0335954;       // 34Na
			case  157: return 35.0406263;       // 35Na
			case  158: return 36.0492964;       // 36Na
			case  159: return 37.0570565;       // 37Na
			case  160: return 19.03416954;      // 19Mg
			case  161: return 20.01885029;      // 20Mg
			case  162: return 21.01171618;      // 21Mg
			case  163: return 21.9995706534;    // 22Mg
			case  164: return 22.9941242174;    // 23Mg
			case  165: return 23.98504169714;   // 24Mg
			case  166: return 24.98583697650;   // 25Mg
			case  167: return 25.98259296831;   // 26Mg
			case  168: return 26.98434062453;   // 27Mg
			case  169: return 27.983876722;     // 28Mg
			case  170: return 28.98861712;      // 29Mg
			case  171: return 29.990462937;     // 30Mg
			case  172: return 30.996648033;     // 31Mg
			case  173: return 31.999110234;     // 32Mg
			case  174: return 33.005327131;     // 33Mg
			case  175: return 34.00893531;      // 34Mg
			case  176: return 35.0167919;       // 35Mg
			case  177: return 36.0218849;       // 36Mg
			case  178: return 37.0303754;       // 37Mg
			case  179: return 38.0365854;       // 38Mg
			case  180: return 39.0453855;       // 39Mg
			case  181: return 40.0521864;       // 40Mg
			case  182: return 21.0289743;       // 21Al
			case  183: return 22.0195443;       // 22Al
			case  184: return 23.0072443537;    // 23Al
			case  185: return 23.999948912;     // 24Al
			case  186: return 24.9904281051;    // 25Al
			case  187: return 25.98689190469;   // 26Al
			case  188: return 26.9815385311;    // 27Al
			case  189: return 27.9819102113;    // 28Al
			case  190: return 28.980456510;     // 29Al
			case  191: return 29.98296015;      // 30Al
			case  192: return 30.98394522;      // 31Al
			case  193: return 31.98808513;      // 32Al
			case  194: return 32.99090981;      // 33Al
			case  195: return 33.99670574;      // 34Al
			case  196: return 34.99976475;      // 35Al
			case  197: return 36.0063911;       // 36Al
			case  198: return 37.0105313;       // 37Al
			case  199: return 38.0174027;       // 38Al
			case  200: return 39.0225454;       // 39Al
			case  201: return 40.0300354;       // 40Al
			case  202: return 41.0363864;       // 41Al
			case  203: return 42.0438464;       // 42Al
			case  204: return 43.0514775;       // 43Al
			case  205: return 22.0357954;       // 22Si
			case  206: return 23.0254454;       // 23Si
			case  207: return 24.01153521;      // 24Si
			case  208: return 25.00410911;      // 25Si
			case  209: return 25.9923338411;    // 26Si
			case  210: return 26.9867048115;    // 27Si
			case  211: return 27.9769265346544; // 28Si
			case  212: return 28.9764946649052; // 29Si
			case  213: return 29.97377013623;   // 30Si
			case  214: return 30.97536319446;   // 31Si
			case  215: return 31.9741515432;    // 32Si
			case  216: return 32.9779769675;    // 33Si
			case  217: return 33.97857615;      // 34Si
			case  218: return 34.98458341;      // 35Si
			case  219: return 35.98669577;      // 36Si
			case  220: return 36.99292189;      // 37Si
			case  221: return 37.99552375;      // 38Si
			case  222: return 39.00249197;      // 39Si
			case  223: return 40.0058325;       // 40Si
			case  224: return 41.0130140;       // 41Si
			case  225: return 42.0177854;       // 42Si
			case  226: return 43.0248064;       // 43Si
			case  227: return 44.0306164;       // 44Si
			case  228: return 45.0399575;       // 45Si
			case  229: return 24.0357754;       // 24P
			case  230: return 25.0211943;       // 25P
			case  231: return 26.0117821;       // 26P
			case  232: return 26.99922428;      // 27P
			case  233: return 27.992326612;     // 28P
			case  234: return 28.9818007960;    // 29P
			case  235: return 29.9783137534;    // 30P
			case  236: return 30.9737619984270; // 31P
			case  237: return 31.97390764342;   // 32P
			case  238: return 32.971725712;     // 33P
			case  239: return 33.9736458987;    // 34P
			case  240: return 34.973314120;     // 35P
			case  241: return 35.97826014;      // 36P
			case  242: return 36.97960741;      // 37P
			case  243: return 37.98425293;      // 38P
			case  244: return 38.98622798;      // 39P
			case  245: return 39.9913312;       // 40P
			case  246: return 40.99465486;      // 41P
			case  247: return 42.0010823;       // 42P
			case  248: return 43.0050240;       // 43P
			case  249: return 44.0112154;       // 44P
			case  250: return 45.0164564;       // 45P
			case  251: return 46.0244675;       // 46P
			case  252: return 47.0313986;       // 47P
			case  253: return 26.0290764;       // 26S
			case  254: return 27.0182843;       // 27S
			case  255: return 28.0043717;       // 28S
			case  256: return 28.99661154;      // 29S
			case  257: return 29.9849070340;    // 30S
			case  258: return 30.9795570125;    // 31S
			case  259: return 31.972071174414;  // 32S
			case  260: return 32.971458909815;  // 33S
			case  261: return 33.96786700447;   // 34S
			case  262: return 34.96903231043;   // 35S
			case  263: return 35.9670807120;    // 36S
			case  264: return 36.9711255121;    // 37S
			case  265: return 37.971163377;     // 38S
			case  266: return 38.97513454;      // 39S
			case  267: return 39.975482643;     // 40S
			case  268: return 40.979593544;     // 41S
			case  269: return 41.981065130;     // 42S
			case  270: return 42.986907653;     // 43S
			case  271: return 43.990118856;     // 44S
			case  272: return 44.9957274;       // 45S
			case  273: return 46.0000454;       // 46S
			case  274: return 47.0079554;       // 47S
			case  275: return 48.0137064;       // 48S
			case  276: return 49.0227672;       // 49S
			case  277: return 28.0295464;       // 28Cl
			case  278: return 29.0147843;       // 29Cl
			case  279: return 30.0047721;       // 30Cl
			case  280: return 30.99241454;      // 31Cl
			case  281: return 31.9856846460;    // 32Cl
			case  282: return 32.9774519942;    // 33Cl
			case  283: return 33.97376248552;   // 34Cl
			case  284: return 34.96885268237;   // 35Cl
			case  285: return 35.96830680938;   // 36Cl
			case  286: return 36.96590260255;   // 37Cl
			case  287: return 37.9680104411;    // 38Cl
			case  288: return 38.968008219;     // 39Cl
			case  289: return 39.97041534;      // 40Cl
			case  290: return 40.97068574;      // 41Cl
			case  291: return 41.9732515;       // 42Cl
			case  292: return 42.9738910;       // 43Cl
			case  293: return 43.9778720;       // 44Cl
			case  294: return 44.9802911;       // 45Cl
			case  295: return 45.9851717;       // 46Cl
			case  296: return 46.9891643;       // 47Cl
			case  297: return 47.9956454;       // 48Cl
			case  298: return 49.0012364;       // 49Cl
			case  299: return 50.0090564;       // 50Cl
			case  300: return 51.0155475;       // 51Cl
			case  301: return 30.0230754;       // 30Ar
			case  302: return 31.0121222;       // 31Ar
			case  303: return 31.997637819;     // 32Ar
			case  304: return 32.9899255543;    // 33Ar
			case  305: return 33.98027009083;   // 34Ar
			case  306: return 34.9752575980;    // 35Ar
			case  307: return 35.96754510528;   // 36Ar
			case  308: return 36.9667763322;    // 37Ar
			case  309: return 37.9627321121;    // 38Ar
			case  310: return 38.964313054;     // 39Ar
			case  311: return 39.962383123724;  // 40Ar
			case  312: return 40.9645005737;    // 41Ar
			case  313: return 41.963045762;     // 42Ar
			case  314: return 42.965636157;     // 43Ar
			case  315: return 43.964923817;     // 44Ar
			case  316: return 44.9680397355;    // 45Ar
			case  317: return 45.96808344;      // 46Ar
			case  318: return 46.97293596;      // 47Ar
			case  319: return 47.9759132;       // 48Ar
			case  320: return 48.9819043;       // 49Ar
			case  321: return 49.9861354;       // 50Ar
			case  322: return 50.9937064;       // 51Ar
			case  323: return 51.9989664;       // 52Ar
			case  324: return 53.0072975;       // 53Ar
			case  325: return 32.0226554;       // 32K
			case  326: return 33.0075621;       // 33K
			case  327: return 33.9986932;       // 34K
			case  328: return 34.9880054155;    // 35K
			case  329: return 35.9813020137;    // 36K
			case  330: return 36.9733758910;    // 37K
			case  331: return 37.9690811221;    // 38K
			case  332: return 38.963706486449;  // 39K
			case  333: return 39.96399816660;   // 40K
			case  334: return 40.961825257941;  // 41K
			case  335: return 41.9624023111;    // 42K
			case  336: return 42.9607347044;    // 43K
			case  337: return 43.9615869945;    // 44K
			case  338: return 44.9606914956;    // 45K
			case  339: return 45.9619815978;    // 46K
			case  340: return 46.961661615;     // 47K
			case  341: return 47.9653411983;    // 48K
			case  342: return 48.9682107586;    // 49K
			case  343: return 49.972380083;     // 50K
			case  344: return 50.97582814;      // 51K
			case  345: return 51.9822443;       // 52K
			case  346: return 52.9874654;       // 53K
			case  347: return 53.9946364;       // 54K
			case  348: return 55.0007675;       // 55K
			case  349: return 56.0085186;       // 56K
			case  350: return 34.0148732;       // 34Ca
			case  351: return 35.0051421;       // 35Ca
			case  352: return 35.99307443;      // 36Ca
			case  353: return 36.9858978568;    // 37Ca
			case  354: return 37.9763192221;    // 38Ca
			case  355: return 38.9707108164;    // 39Ca
			case  356: return 39.96259086322;   // 40Ca
			case  357: return 40.9622779215;    // 41Ca
			case  358: return 41.9586178316;    // 42Ca
			case  359: return 42.9587664424;    // 43Ca
			case  360: return 43.9554815635;    // 44Ca
			case  361: return 44.9561863539;    // 45Ca
			case  362: return 45.953689024;     // 46Ca
			case  363: return 46.954542424;     // 47Ca
			case  364: return 47.9525227613;    // 48Ca
			case  365: return 48.9556627423;    // 49Ca
			case  366: return 49.957499217;     // 50Ca
			case  367: return 50.96098924;      // 51Ca
			case  368: return 51.96321764;      // 52Ca
			case  369: return 52.9694543;       // 53Ca
			case  370: return 53.9734054;       // 54Ca
			case  371: return 54.9803054;       // 55Ca
			case  372: return 55.9850864;       // 56Ca
			case  373: return 56.9926264;       // 57Ca
			case  374: return 57.9979475;       // 58Ca
			case  375: return 36.0164832;       // 36Sc
			case  376: return 37.0037432;       // 37Sc
			case  377: return 37.9951221;       // 38Sc
			case  378: return 38.98478526;      // 39Sc
			case  379: return 39.977967330;     // 40Sc
			case  380: return 40.96925110588;   // 41Sc
			case  381: return 41.9655165318;    // 42Sc
			case  382: return 42.961150520;     // 43Sc
			case  383: return 43.959402919;     // 44Sc
			case  384: return 44.9559082877;    // 45Sc
			case  385: return 45.9551682678;    // 46Sc
			case  386: return 46.952403721;     // 47Sc
			case  387: return 47.952223653;     // 48Sc
			case  388: return 48.950014629;     // 49Sc
			case  389: return 49.95217616;      // 50Sc
			case  390: return 50.95359221;      // 51Sc
			case  391: return 51.9568815;       // 52Sc
			case  392: return 52.9590929;       // 53Sc
			case  393: return 53.9639339;       // 54Sc
			case  394: return 54.9678250;       // 55Sc
			case  395: return 55.9734543;       // 56Sc
			case  396: return 56.9777754;       // 57Sc
			case  397: return 57.9840364;       // 58Sc
			case  398: return 58.9889464;       // 59Sc
			case  399: return 59.9956575;       // 60Sc
			case  400: return 61.0010086;       // 61Sc
			case  401: return 38.0114532;       // 38Ti
			case  402: return 39.0023622;       // 39Ti
			case  403: return 39.9905017;       // 40Ti
			case  404: return 40.98314830;      // 41Ti
			case  405: return 41.9730490330;    // 42Ti
			case  406: return 42.968522578;     // 43Ti
			case  407: return 43.9596899575;    // 44Ti
			case  408: return 44.9581219895;    // 45Ti
			case  409: return 45.9526277235;    // 46Ti
			case  410: return 46.9517587938;    // 47Ti
			case  411: return 47.9479419838;    // 48Ti
			case  412: return 48.9478656839;    // 49Ti
			case  413: return 49.9447868939;    // 50Ti
			case  414: return 50.9466106565;    // 51Ti
			case  415: return 51.946893076;     // 52Ti
			case  416: return 52.9497311;       // 53Ti
			case  417: return 53.9510513;       // 54Ti
			case  418: return 54.9552717;       // 55Ti
			case  419: return 55.9579115;       // 56Ti
			case  420: return 56.9636427;       // 57Ti
			case  421: return 57.9666043;       // 58Ti
			case  422: return 58.9724743;       // 59Ti
			case  423: return 59.9760354;       // 60Ti
			case  424: return 60.9824564;       // 61Ti
			case  425: return 61.9865175;       // 62Ti
			case  426: return 62.9937575;       // 63Ti
			case  427: return 40.0127643;       // 40V
			case  428: return 41.0002132;       // 41V
			case  429: return 41.9918232;       // 42V
			case  430: return 42.98076646;      // 43V
			case  431: return 43.9741120;       // 44V
			case  432: return 44.965774886;     // 45V
			case  433: return 45.9601987836;    // 46V
			case  434: return 46.9549049136;    // 47V
			case  435: return 47.952252211;     // 48V
			case  436: return 48.9485118096;    // 49V
			case  437: return 49.9471560195;    // 50V
			case  438: return 50.9439570494;    // 51V
			case  439: return 51.9447730195;    // 52V
			case  440: return 52.944336734;     // 53V
			case  441: return 53.94643916;      // 54V
			case  442: return 54.9472410;       // 55V
			case  443: return 55.9504819;       // 56V
			case  444: return 56.9525224;       // 57V
			case  445: return 57.9567214;       // 58V
			case  446: return 58.9593917;       // 59V
			case  447: return 59.9643124;       // 60V
			case  448: return 60.9672596;       // 61V
			case  449: return 61.9726532;       // 62V
			case  450: return 62.9763943;       // 63V
			case  451: return 63.9826443;       // 64V
			case  452: return 64.9875054;       // 65V
			case  453: return 65.9939864;       // 66V
			case  454: return 42.0067043;       // 42Cr
			case  455: return 42.9975343;       // 43Cr
			case  456: return 43.9853632;       // 44Cr
			case  457: return 44.97905038;      // 45Cr
			case  458: return 45.96835921;      // 46Cr
			case  459: return 46.962897475;     // 47Cr
			case  460: return 47.954029179;     // 48Cr
			case  461: return 48.951333325;     // 49Cr
			case  462: return 49.9460418394;    // 50Cr
			case  463: return 50.9447650294;    // 51Cr
			case  464: return 51.9405062363;    // 52Cr
			case  465: return 52.9406481562;    // 53Cr
			case  466: return 53.9388791661;    // 54Cr
			case  467: return 54.9408384364;    // 55Cr
			case  468: return 55.940653120;     // 56Cr
			case  469: return 56.943613020;     // 57Cr
			case  470: return 57.9443522;       // 58Cr
			case  471: return 58.9485926;       // 59Cr
			case  472: return 59.9500823;       // 60Cr
			case  473: return 60.9544214;       // 61Cr
			case  474: return 61.9561016;       // 62Cr
			case  475: return 62.9616549;       // 63Cr
			case  476: return 63.9640832;       // 64Cr
			case  477: return 64.9699632;       // 65Cr
			case  478: return 65.9736654;       // 66Cr
			case  479: return 66.9801654;       // 67Cr
			case  480: return 67.9840375;       // 68Cr
			case  481: return 44.0071554;       // 44Mn
			case  482: return 44.9944943;       // 45Mn
			case  483: return 45.9860943;       // 46Mn
			case  484: return 46.97577534;      // 47Mn
			case  485: return 47.9685218;       // 48Mn
			case  486: return 48.95959511;      // 49Mn
			case  487: return 49.9542377895;    // 50Mn
			case  488: return 50.9482084794;    // 51Mn
			case  489: return 51.945563920;     // 52Mn
			case  490: return 52.9412888968;    // 53Mn
			case  491: return 53.940357612;     // 54Mn
			case  492: return 54.9380439148;    // 55Mn
			case  493: return 55.9389036949;    // 56Mn
			case  494: return 56.938286116;     // 57Mn
			case  495: return 57.940066629;     // 58Mn
			case  496: return 58.940391125;     // 59Mn
			case  497: return 59.943136625;     // 60Mn
			case  498: return 60.944452525;     // 61Mn
			case  499: return 61.9479516;       // 62Mn
			case  500: return 62.949664740;     // 63Mn
			case  501: return 63.953849438;     // 64Mn
			case  502: return 64.956019840;     // 65Mn
			case  503: return 65.96054712;      // 66Mn
			case  504: return 66.9642443;       // 67Mn
			case  505: return 67.9696254;       // 68Mn
			case  506: return 68.9736664;       // 69Mn
			case  507: return 69.9793775;       // 70Mn
			case  508: return 70.9836875;       // 71Mn
			case  509: return 45.0144243;       // 45Fe
			case  510: return 46.0006354;       // 46Fe
			case  511: return 46.9918554;       // 47Fe
			case  512: return 47.9802343;       // 48Fe
			case  513: return 48.97342926;      // 49Fe
			case  514: return 49.96297564;      // 50Fe
			case  515: return 50.956841096;     // 51Fe
			case  516: return 51.948113170;     // 52Fe
			case  517: return 52.945306418;     // 53Fe
			case  518: return 53.9396089953;    // 54Fe
			case  519: return 54.9382919951;    // 55Fe
			case  520: return 55.9349363349;    // 56Fe
			case  521: return 56.9353928449;    // 57Fe
			case  522: return 57.9332744353;    // 58Fe
			case  523: return 58.9348743454;    // 59Fe
			case  524: return 59.934071137;     // 60Fe
			case  525: return 60.936746228;     // 61Fe
			case  526: return 61.936791830;     // 62Fe
			case  527: return 62.940272746;     // 63Fe
			case  528: return 63.940987854;     // 64Fe
			case  529: return 64.945011573;     // 65Fe
			case  530: return 65.946250044;     // 66Fe
			case  531: return 66.9505423;       // 67Fe
			case  532: return 67.9529539;       // 68Fe
			case  533: return 68.9580743;       // 69Fe
			case  534: return 69.9610254;       // 70Fe
			case  535: return 70.9667264;       // 71Fe
			case  536: return 71.9698375;       // 72Fe
			case  537: return 72.9757275;       // 73Fe
			case  538: return 73.9793586;       // 74Fe
			case  539: return 47.0105786;       // 47Co
			case  540: return 48.0009386;       // 48Co
			case  541: return 48.9889175;       // 49Co
			case  542: return 49.9809164;       // 50Co
			case  543: return 50.97064752;      // 51Co
			case  544: return 51.9635121;       // 52Co
			case  545: return 52.954204119;     // 53Co
			case  546: return 53.9484598754;    // 54Co
			case  547: return 54.9419972057;    // 55Co
			case  548: return 55.9398388063;    // 56Co
			case  549: return 56.9362905766;    // 57Co
			case  550: return 57.935752113;     // 58Co
			case  551: return 58.9331942956;    // 59Co
			case  552: return 59.9338163056;    // 60Co
			case  553: return 60.9324766295;    // 61Co
			case  554: return 61.93405920;      // 62Co
			case  555: return 62.93360020;      // 63Co
			case  556: return 63.93581121;      // 64Co
			case  557: return 64.936462122;     // 65Co
			case  558: return 65.93944315;      // 66Co
			case  559: return 66.940609669;     // 67Co
			case  560: return 67.9442616;       // 68Co
			case  561: return 68.9461420;       // 69Co
			case  562: return 69.9496332;       // 70Co
			case  563: return 70.9523750;       // 71Co
			case  564: return 71.9572943;       // 72Co
			case  565: return 72.9603954;       // 73Co
			case  566: return 73.9651564;       // 74Co
			case  567: return 74.9687675;       // 75Co
			case  568: return 75.9741386;       // 76Co
			case  569: return 48.0176954;       // 48Ni
			case  570: return 49.0077086;       // 49Ni
			case  571: return 49.9947486;       // 50Ni
			case  572: return 50.9861186;       // 51Ni
			case  573: return 51.9748075;       // 52Ni
			case  574: return 52.96819027;      // 53Ni
			case  575: return 53.95789254;      // 54Ni
			case  576: return 54.9513306385;    // 55Ni
			case  577: return 55.9421285557;    // 56Ni
			case  578: return 56.9397921871;    // 57Ni
			case  579: return 57.9353424152;    // 58Ni
			case  580: return 58.9343462052;    // 59Ni
			case  581: return 59.9307858852;    // 60Ni
			case  582: return 60.9310555752;    // 61Ni
			case  583: return 61.9283453755;    // 62Ni
			case  584: return 62.9296696356;    // 63Ni
			case  585: return 63.9279668258;    // 64Ni
			case  586: return 64.9300851760;    // 65Ni
			case  587: return 65.929139315;     // 66Ni
			case  588: return 66.931569431;     // 67Ni
			case  589: return 67.931868832;     // 68Ni
			case  590: return 68.935610340;     // 69Ni
			case  591: return 69.936431323;     // 70Ni
			case  592: return 70.940519024;     // 71Ni
			case  593: return 71.941785924;     // 72Ni
			case  594: return 72.946206726;     // 73Ni
			case  595: return 73.9479843;       // 74Ni
			case  596: return 74.9525032;       // 75Ni
			case  597: return 75.9553354;       // 76Ni
			case  598: return 76.9605554;       // 77Ni
			case  599: return 77.9633686;       // 78Ni
			case  600: return 78.9702586;       // 79Ni
			case  601: return 51.9967186;       // 52Cu
			case  602: return 52.9845986;       // 53Cu
			case  603: return 53.9766654;       // 54Cu
			case  604: return 54.9660417;       // 55Cu
			case  605: return 55.9589521;       // 56Cu
			case  606: return 56.9492125066;    // 57Cu
			case  607: return 57.9445330570;    // 58Cu
			case  608: return 58.9394974867;    // 59Cu
			case  609: return 59.937364518;     // 60Cu
			case  610: return 60.933457610;     // 61Cu
			case  611: return 61.9325954175;    // 62Cu
			case  612: return 62.9295977256;    // 63Cu
			case  613: return 63.9297643456;    // 64Cu
			case  614: return 64.9277897071;    // 65Cu
			case  615: return 65.9288690372;    // 66Cu
			case  616: return 66.927730313;     // 67Cu
			case  617: return 67.929610917;     // 68Cu
			case  618: return 68.929429315;     // 69Cu
			case  619: return 69.932392112;     // 70Cu
			case  620: return 70.932676816;     // 71Cu
			case  621: return 71.935820315;     // 72Cu
			case  622: return 72.936674421;     // 73Cu
			case  623: return 73.939874966;     // 74Cu
			case  624: return 74.941522625;     // 75Cu
			case  625: return 75.945275072;     // 76Cu
			case  626: return 76.9479216;       // 77Cu
			case  627: return 77.9522354;       // 78Cu
			case  628: return 78.9550243;       // 79Cu
			case  629: return 79.9608964;       // 80Cu
			case  630: return 80.9658786;       // 81Cu
			case  631: return 81.9724486;       // 82Cu
			case  632: return 53.9920475;       // 54Zn
			case  633: return 54.9839875;       // 55Zn
			case  634: return 55.9725454;       // 56Zn
			case  635: return 56.9650622;       // 57Zn
			case  636: return 57.95459154;      // 58Zn
			case  637: return 58.9493126689;    // 59Zn
			case  638: return 59.9418421069;    // 60Zn
			case  639: return 60.93950717;      // 61Zn
			case  640: return 61.9343339773;    // 62Zn
			case  641: return 62.933211517;     // 63Zn
			case  642: return 63.9291420171;    // 64Zn
			case  643: return 64.9292407771;    // 65Zn
			case  644: return 65.9260338194;    // 66Zn
			case  645: return 66.9271277596;    // 67Zn
			case  646: return 67.9248445598;    // 68Zn
			case  647: return 68.926550710;     // 69Zn
			case  648: return 69.925319221;     // 70Zn
			case  649: return 70.927719628;     // 71Zn
			case  650: return 71.926842823;     // 72Zn
			case  651: return 72.929582620;     // 73Zn
			case  652: return 73.929407327;     // 74Zn
			case  653: return 74.932840221;     // 75Zn
			case  654: return 75.933115016;     // 76Zn
			case  655: return 76.936887221;     // 77Zn
			case  656: return 77.938289221;     // 78Zn
			case  657: return 78.942638124;     // 79Zn
			case  658: return 79.944552928;     // 80Zn
			case  659: return 80.950402654;     // 81Zn
			case  660: return 81.9542632;       // 82Zn
			case  661: return 82.9605654;       // 83Zn
			case  662: return 83.9652164;       // 84Zn
			case  663: return 84.9722675;       // 85Zn
			case  664: return 55.9953664;       // 56Ga
			case  665: return 56.9832032;       // 57Ga
			case  666: return 57.9747821;       // 58Ga
			case  667: return 58.9635318;       // 59Ga
			case  668: return 59.9572921;       // 60Ga
			case  669: return 60.94939941;      // 61Ga
			case  670: return 61.9441902575;    // 62Ga
			case  671: return 62.939294214;     // 63Ga
			case  672: return 63.936840415;     // 64Ga
			case  673: return 64.9327345988;    // 65Ga
			case  674: return 65.931589434;     // 66Ga
			case  675: return 66.928202513;     // 67Ga
			case  676: return 67.927980516;     // 68Ga
			case  677: return 68.925573513;     // 69Ga
			case  678: return 69.926021913;     // 70Ga
			case  679: return 70.9247025887;    // 71Ga
			case  680: return 71.9263674788;    // 72Ga
			case  681: return 72.925174718;     // 73Ga
			case  682: return 73.926945732;     // 74Ga
			case  683: return 74.926500226;     // 75Ga
			case  684: return 75.928827621;     // 76Ga
			case  685: return 76.929154326;     // 77Ga
			case  686: return 77.931608820;     // 78Ga
			case  687: return 78.932852320;     // 79Ga
			case  688: return 79.936420831;     // 80Ga
			case  689: return 80.938133835;     // 81Ga
			case  690: return 81.943176526;     // 82Ga
			case  691: return 82.947120328;     // 83Ga
			case  692: return 83.9524643;       // 84Ga
			case  693: return 84.9569932;       // 85Ga
			case  694: return 85.9630175;       // 86Ga
			case  695: return 86.9682486;       // 87Ga
			case  696: return 57.9917243;       // 58Ge
			case  697: return 58.9824932;       // 59Ge
			case  698: return 59.9703621;       // 60Ge
			case  699: return 60.9637932;       // 61Ge
			case  700: return 61.9550215;       // 62Ge
			case  701: return 62.94962840;      // 63Ge
			case  702: return 63.941689940;     // 64Ge
			case  703: return 64.939368123;     // 65Ge
			case  704: return 65.933862126;     // 66Ge
			case  705: return 66.932733950;     // 67Ge
			case  706: return 67.928095320;     // 68Ge
			case  707: return 68.927964514;     // 69Ge
			case  708: return 69.9242487590;    // 70Ge
			case  709: return 70.9249523390;    // 71Ge
			case  710: return 71.92207582681;   // 72Ge
			case  711: return 72.92345895661;   // 73Ge
			case  712: return 73.92117776113;   // 74Ge
			case  713: return 74.92285837055;   // 75Ge
			case  714: return 75.92140272619;   // 76Ge
			case  715: return 76.92354984357;   // 77Ge
			case  716: return 77.922852938;     // 78Ge
			case  717: return 78.92536040;      // 79Ge
			case  718: return 79.925350822;     // 80Ge
			case  719: return 80.928832922;     // 81Ge
			case  720: return 81.929774024;     // 82Ge
			case  721: return 82.934539126;     // 83Ge
			case  722: return 83.937575134;     // 84Ge
			case  723: return 84.942969740;     // 85Ge
			case  724: return 85.9465832;       // 86Ge
			case  725: return 86.9526843;       // 87Ge
			case  726: return 87.9569154;       // 88Ge
			case  727: return 88.9637964;       // 89Ge
			case  728: return 89.9686375;       // 90Ge
			case  729: return 59.9938843;       // 60As
			case  730: return 60.9811232;       // 61As
			case  731: return 61.9736132;       // 62As
			case  732: return 62.9639021;       // 63As
			case  733: return 63.9574333;       // 64As
			case  734: return 64.94961191;      // 65As
			case  735: return 65.944148861;     // 66As
			case  736: return 66.9392511148;    // 67As
			case  737: return 67.936774120;     // 68As
			case  738: return 68.93224634;      // 69As
			case  739: return 69.93092654;      // 70As
			case  740: return 70.927113845;     // 71As
			case  741: return 71.926752344;     // 72As
			case  742: return 72.923829141;     // 73As
			case  743: return 73.923928618;     // 74As
			case  744: return 74.9215945795;    // 75As
			case  745: return 75.9223920295;    // 76As
			case  746: return 76.920647618;     // 77As
			case  747: return 77.92182811;      // 78As
			case  748: return 78.920948458;     // 79As
			case  749: return 79.922474636;     // 80As
			case  750: return 80.922132329;     // 81As
			case  751: return 81.924741246;     // 82As
			case  752: return 82.925206930;     // 83As
			case  753: return 83.929303334;     // 84As
			case  754: return 84.932163733;     // 85As
			case  755: return 85.936701537;     // 86As
			case  756: return 86.940291732;     // 87As
			case  757: return 87.9455521;       // 88As
			case  758: return 88.9497632;       // 89As
			case  759: return 89.9556364;       // 90As
			case  760: return 90.9603964;       // 91As
			case  761: return 91.9667475;       // 92As
			case  762: return 63.9710954;       // 64Se
			case  763: return 64.9644064;       // 65Se
			case  764: return 65.9555932;       // 66Se
			case  765: return 66.94999472;      // 67Se
			case  766: return 67.9418252453;    // 68Se
			case  767: return 68.939414816;     // 69Se
			case  768: return 69.933515517;     // 70Se
			case  769: return 70.932209430;     // 71Se
			case  770: return 71.927140521;     // 72Se
			case  771: return 72.926754980;     // 73Se
			case  772: return 73.92247593415;   // 74Se
			case  773: return 74.92252287078;   // 75Se
			case  774: return 75.91921370417;   // 76Se
			case  775: return 76.91991415467;   // 77Se
			case  776: return 77.9173092820;    // 78Se
			case  777: return 78.9184992924;    // 79Se
			case  778: return 79.916521813;     // 80Se
			case  779: return 80.917993014;     // 81Se
			case  780: return 81.916699515;     // 82Se
			case  781: return 82.919118636;     // 83Se
			case  782: return 83.918466821;     // 84Se
			case  783: return 84.922260828;     // 85Se
			case  784: return 85.924311727;     // 86Se
			case  785: return 86.928688624;     // 87Se
			case  786: return 87.931417536;     // 88Se
			case  787: return 88.936669140;     // 89Se
			case  788: return 89.9401035;       // 90Se
			case  789: return 90.9459654;       // 91Se
			case  790: return 91.9498464;       // 92Se
			case  791: return 92.9562986;       // 93Se
			case  792: return 93.9604986;       // 94Se
			case  793: return 94.9673086;       // 95Se
			case  794: return 66.9646554;       // 67Br
			case  795: return 67.9587333;       // 68Br
			case  796: return 68.95049740;      // 69Br
			case  797: return 69.94479216;      // 70Br
			case  798: return 70.939342258;     // 71Br
			case  799: return 71.936588672;     // 72Br
			case  800: return 72.931671578;     // 73Br
			case  801: return 73.929910263;     // 74Br
			case  802: return 74.925810546;     // 75Br
			case  803: return 75.92454210;      // 76Br
			case  804: return 76.921379230;     // 77Br
			case  805: return 77.921145938;     // 78Br
			case  806: return 78.918337614;     // 79Br
			case  807: return 79.918529814;     // 80Br
			case  808: return 80.916289714;     // 81Br
			case  809: return 81.916803214;     // 82Br
			case  810: return 82.915175641;     // 83Br
			case  811: return 83.91649628;      // 84Br
			case  812: return 84.915645833;     // 85Br
			case  813: return 85.918805433;     // 86Br
			case  814: return 86.920674034;     // 87Br
			case  815: return 87.924083334;     // 88Br
			case  816: return 88.926704635;     // 89Br
			case  817: return 89.931292836;     // 90Br
			case  818: return 90.934398638;     // 91Br
			case  819: return 91.939631672;     // 92Br
			case  820: return 92.9431348;       // 93Br
			case  821: return 93.9489043;       // 94Br
			case  822: return 94.9530121;       // 95Br
			case  823: return 95.9590332;       // 96Br
			case  824: return 96.9634443;       // 97Br
			case  825: return 97.9694643;       // 98Br
			case  826: return 68.9651843;       // 69Kr
			case  827: return 69.9560421;       // 70Kr
			case  828: return 70.9502714;       // 71Kr
			case  829: return 71.942092486;     // 72Kr
			case  830: return 72.939289271;     // 73Kr
			case  831: return 73.933084022;     // 74Kr
			case  832: return 74.930945787;     // 75Kr
			case  833: return 75.925910343;     // 76Kr
			case  834: return 76.924670021;     // 77Kr
			case  835: return 77.9203649476;    // 78Kr
			case  836: return 78.920082938;     // 79Kr
			case  837: return 79.9163780875;    // 80Kr
			case  838: return 80.916591215;     // 81Kr
			case  839: return 81.9134827394;    // 82Kr
			case  840: return 82.9141271632;    // 83Kr
			case  841: return 83.911497728244;  // 84Kr
			case  842: return 84.912527321;     // 85Kr
			case  843: return 85.910610626941;  // 86Kr
			case  844: return 86.9133547626;    // 87Kr
			case  845: return 87.914447928;     // 88Kr
			case  846: return 88.917835523;     // 89Kr
			case  847: return 89.919527920;     // 90Kr
			case  848: return 90.923806324;     // 91Kr
			case  849: return 91.926173129;     // 92Kr
			case  850: return 92.931147227;     // 93Kr
			case  851: return 93.93414013;      // 94Kr
			case  852: return 94.93971120;      // 95Kr
			case  853: return 95.94301722;      // 96Kr
			case  854: return 96.9490914;       // 97Kr
			case  855: return 97.9524332;       // 98Kr
			case  856: return 98.9583954;       // 99Kr
			case  857: return 99.9623743;       // 100Kr
			case  858: return 100.9687354;      // 101Kr
			case  859: return 70.9653254;       // 71Rb
			case  860: return 71.9590854;       // 72Rb
			case  861: return 72.9505311;       // 73Rb
			case  862: return 73.944265932;     // 74Rb
			case  863: return 74.938573213;     // 75Rb
			case  864: return 75.935073010;     // 76Rb
			case  865: return 76.930401614;     // 77Rb
			case  866: return 77.928141935;     // 78Rb
			case  867: return 78.923989923;     // 79Rb
			case  868: return 79.922516420;     // 80Rb
			case  869: return 80.918993953;     // 81Rb
			case  870: return 81.918209032;     // 82Rb
			case  871: return 82.915114225;     // 83Rb
			case  872: return 83.914375224;     // 84Rb
			case  873: return 84.911789737954;  // 85Rb
			case  874: return 85.9111674321;    // 86Rb
			case  875: return 86.909180531060;  // 87Rb
			case  876: return 87.9113155917;    // 88Rb
			case  877: return 88.912278359;     // 89Rb
			case  878: return 89.914798570;     // 90Rb
			case  879: return 90.916537284;     // 91Rb
			case  880: return 91.919728466;     // 92Rb
			case  881: return 92.922039384;     // 93Rb
			case  882: return 93.926394822;     // 94Rb
			case  883: return 94.92926022;      // 95Rb
			case  884: return 95.934133436;     // 96Rb
			case  885: return 96.937177121;     // 97Rb
			case  886: return 97.941686937;     // 98Rb
			case  887: return 98.9450312;       // 99Rb
			case  888: return 99.9500321;       // 100Rb
			case  889: return 100.9540423;      // 101Rb
			case  890: return 101.9595232;      // 102Rb
			case  891: return 102.9639243;      // 103Rb
			case  892: return 72.9657043;       // 73Sr
			case  893: return 73.9561711;       // 74Sr
			case  894: return 74.9499524;       // 75Sr
			case  895: return 75.94176337;      // 76Sr
			case  896: return 76.937945585;     // 77Sr
			case  897: return 77.932180080;     // 78Sr
			case  898: return 78.929707790;     // 79Sr
			case  899: return 79.924517537;     // 80Sr
			case  900: return 80.923211434;     // 81Sr
			case  901: return 81.918399964;     // 82Sr
			case  902: return 82.917554473;     // 83Sr
			case  903: return 83.913419113;     // 84Sr
			case  904: return 84.912932030;     // 85Sr
			case  905: return 85.909260612;     // 86Sr
			case  906: return 86.908877512;     // 87Sr
			case  907: return 87.905612512;     // 88Sr
			case  908: return 88.907451112;     // 89Sr
			case  909: return 89.907730028;     // 90Sr
			case  910: return 90.910195461;     // 91Sr
			case  911: return 91.911038237;     // 92Sr
			case  912: return 92.914024281;     // 93Sr
			case  913: return 93.915355618;     // 94Sr
			case  914: return 94.919352963;     // 95Sr
			case  915: return 95.921706693;     // 96Sr
			case  916: return 96.926374036;     // 97Sr
			case  917: return 97.928688840;     // 98Sr
			case  918: return 98.932890738;     // 99Sr
			case  919: return 99.93577010;      // 100Sr
			case  920: return 100.94035286;     // 101Sr
			case  921: return 101.94379175;     // 102Sr
			case  922: return 102.9490921;      // 103Sr
			case  923: return 103.9526532;      // 104Sr
			case  924: return 104.9585554;      // 105Sr
			case  925: return 105.9626564;      // 106Sr
			case  926: return 106.9689775;      // 107Sr
			case  927: return 75.9585654;       // 76Y
			case  928: return 76.94978165;      // 77Y
			case  929: return 77.9436143;       // 78Y
			case  930: return 78.9373548;       // 79Y
			case  931: return 79.934356167;     // 80Y
			case  932: return 80.929455658;     // 81Y
			case  933: return 81.926931459;     // 82Y
			case  934: return 82.92248520;      // 83Y
			case  935: return 83.920672146;     // 84Y
			case  936: return 84.91643320;      // 85Y
			case  937: return 85.91488615;      // 86Y
			case  938: return 86.910876117;     // 87Y
			case  939: return 87.909501620;     // 88Y
			case  940: return 88.905840324;     // 89Y
			case  941: return 89.907143924;     // 90Y
			case  942: return 90.907297428;     // 91Y
			case  943: return 91.908945199;     // 92Y
			case  944: return 92.90957811;      // 93Y
			case  945: return 93.911590669;     // 94Y
			case  946: return 94.912816174;     // 95Y
			case  947: return 95.915896869;     // 96Y
			case  948: return 96.918274175;     // 97Y
			case  949: return 97.922382188;     // 98Y
			case  950: return 98.924148074;     // 99Y
			case  951: return 99.92771512;      // 100Y
			case  952: return 100.930147779;    // 101Y
			case  953: return 101.934327744;    // 102Y
			case  954: return 102.93724312;     // 103Y
			case  955: return 103.9419643;      // 104Y
			case  956: return 104.9454454;      // 105Y
			case  957: return 105.9505654;      // 106Y
			case  958: return 106.9545254;      // 107Y
			case  959: return 107.9599664;      // 108Y
			case  960: return 108.9643675;      // 109Y
			case  961: return 77.9556654;       // 78Zr
			case  962: return 78.9494843;       // 79Zr
			case  963: return 79.940416;        // 80Zr
			case  964: return 80.9373118;       // 81Zr
			case  965: return 81.9313522;       // 82Zr
			case  966: return 82.929242169;     // 83Zr
			case  967: return 83.923326959;     // 84Zr
			case  968: return 84.921444469;     // 85Zr
			case  969: return 85.916297238;     // 86Zr
			case  970: return 86.914818045;     // 87Zr
			case  971: return 87.910221358;     // 88Zr
			case  972: return 88.908881437;     // 89Zr
			case  973: return 89.904697720;     // 90Zr
			case  974: return 90.905639620;     // 91Zr
			case  975: return 91.905034720;     // 92Zr
			case  976: return 92.906469920;     // 93Zr
			case  977: return 93.906310820;     // 94Zr
			case  978: return 94.908038519;     // 95Zr
			case  979: return 95.908271421;     // 96Zr
			case  980: return 96.910951221;     // 97Zr
			case  981: return 97.912728993;     // 98Zr
			case  982: return 98.91666711;      // 99Zr
			case  983: return 99.918000689;     // 100Zr
			case  984: return 100.921448091;    // 101Zr
			case  985: return 101.923140997;    // 102Zr
			case  986: return 102.92719110;     // 103Zr
			case  987: return 103.92943610;     // 104Zr
			case  988: return 104.93400813;     // 105Zr
			case  989: return 105.9367621;      // 106Zr
			case  990: return 106.9417432;      // 107Zr
			case  991: return 107.9448743;      // 108Zr
			case  992: return 108.9504154;      // 109Zr
			case  993: return 109.9539664;      // 110Zr
			case  994: return 110.9596875;      // 111Zr
			case  995: return 111.9637075;      // 112Zr
			case  996: return 80.9496043;       // 81Nb
			case  997: return 81.9439632;       // 82Nb
			case  998: return 82.9372932;       // 83Nb
			case  999: return 83.9344932;       // 84Nb
			case 1000: return 84.928845844;     // 85Nb
			case 1001: return 85.925782859;     // 86Nb
			case 1002: return 86.920693773;     // 87Nb
			case 1003: return 87.91822261;      // 88Nb
			case 1004: return 88.91344525;      // 89Nb
			case 1005: return 89.911258438;     // 90Nb
			case 1006: return 90.906989737;     // 91Nb
			case 1007: return 91.907188126;     // 92Nb
			case 1008: return 92.906373020;     // 93Nb
			case 1009: return 93.907278820;     // 94Nb
			case 1010: return 94.9068324071;    // 95Nb
			case 1011: return 95.908097335;     // 96Nb
			case 1012: return 96.908095919;     // 97Nb
			case 1013: return 97.910326558;     // 98Nb
			case 1014: return 98.91161313;      // 99Nb
			case 1015: return 99.914327688;     // 100Nb
			case 1016: return 100.915310342;    // 101Nb
			case 1017: return 101.918077235;    // 102Nb
			case 1018: return 102.919457244;    // 103Nb
			case 1019: return 103.922892537;    // 104Nb
			case 1020: return 104.924946545;    // 105Nb
			case 1021: return 105.928931746;    // 106Nb
			case 1022: return 106.931593787;    // 107Nb
			case 1023: return 107.936074888;    // 108Nb
			case 1024: return 108.9392256;      // 109Nb
			case 1025: return 109.9440321;      // 110Nb
			case 1026: return 110.9475332;      // 111Nb
			case 1027: return 111.9524732;      // 112Nb
			case 1028: return 112.9565143;      // 113Nb
			case 1029: return 113.9620154;      // 114Nb
			case 1030: return 114.9663454;      // 115Nb
			case 1031: return 82.9498843;       // 83Mo
			case 1032: return 83.9414943;       // 84Mo
			case 1033: return 84.93826117;      // 85Mo
			case 1034: return 85.931174840;     // 86Mo
			case 1035: return 86.928196231;     // 87Mo
			case 1036: return 87.921967841;     // 88Mo
			case 1037: return 88.919468242;     // 89Mo
			case 1038: return 89.913930938;     // 90Mo
			case 1039: return 90.911745367;     // 91Mo
			case 1040: return 91.9068079684;    // 92Mo
			case 1041: return 92.9068095884;    // 93Mo
			case 1042: return 93.9050849048;    // 94Mo
			case 1043: return 94.9058387747;    // 95Mo
			case 1044: return 95.9046761247;    // 96Mo
			case 1045: return 96.9060181249;    // 97Mo
			case 1046: return 97.9054048249;    // 98Mo
			case 1047: return 98.9077085152;    // 99Mo
			case 1048: return 99.907471811;     // 100Mo
			case 1049: return 100.910341411;    // 101Mo
			case 1050: return 101.910283491;    // 102Mo
			case 1051: return 102.91307910;     // 103Mo
			case 1052: return 103.913734498;    // 104Mo
			case 1053: return 104.91696910;     // 105Mo
			case 1054: return 105.91825910;     // 106Mo
			case 1055: return 106.92210610;     // 107Mo
			case 1056: return 107.92403310;     // 108Mo
			case 1057: return 108.92842412;     // 109Mo
			case 1058: return 109.93070426;     // 110Mo
			case 1059: return 110.93565414;     // 111Mo
			case 1060: return 111.9383121;      // 112Mo
			case 1061: return 112.9433532;      // 113Mo
			case 1062: return 113.9465332;      // 114Mo
			case 1063: return 114.9519643;      // 115Mo
			case 1064: return 115.9554554;      // 116Mo
			case 1065: return 116.9611754;      // 117Mo
			case 1066: return 84.9505843;       // 85Tc
			case 1067: return 85.9449332;       // 86Tc
			case 1068: return 86.938067245;     // 87Tc
			case 1069: return 87.9337816;       // 88Tc
			case 1070: return 88.927648741;     // 89Tc
			case 1071: return 89.924073911;     // 90Tc
			case 1072: return 90.918425425;     // 91Tc
			case 1073: return 91.915269833;     // 92Tc
			case 1074: return 92.910246014;     // 93Tc
			case 1075: return 93.909653644;     // 94Tc
			case 1076: return 94.907653655;     // 95Tc
			case 1077: return 95.907868055;     // 96Tc
			case 1078: return 96.906366740;     // 97Tc
			case 1079: return 97.907212436;     // 98Tc
			case 1080: return 98.906250810;     // 99Tc
			case 1081: return 99.907653915;     // 100Tc
			case 1082: return 100.90730926;     // 101Tc
			case 1083: return 101.909209799;    // 102Tc
			case 1084: return 102.90917611;     // 103Tc
			case 1085: return 103.91142527;     // 104Tc
			case 1086: return 104.91165538;     // 105Tc
			case 1087: return 105.91435813;     // 106Tc
			case 1088: return 106.915460693;    // 107Tc
			case 1089: return 107.918495794;    // 108Tc
			case 1090: return 108.92025610;     // 109Tc
			case 1091: return 109.92374410;     // 110Tc
			case 1092: return 110.92590111;     // 111Tc
			case 1093: return 111.929945860;    // 112Tc
			case 1094: return 112.932569036;    // 113Tc
			case 1095: return 113.9369111;      // 114Tc
			case 1096: return 114.9399821;      // 115Tc
			case 1097: return 115.9447632;      // 116Tc
			case 1098: return 116.9480643;      // 117Tc
			case 1099: return 117.9529943;      // 118Tc
			case 1100: return 118.9566654;      // 119Tc
			case 1101: return 119.9618754;      // 120Tc
			case 1102: return 86.9506943;       // 87Ru
			case 1103: return 87.9416032;       // 88Ru
			case 1104: return 88.9376232;       // 89Ru
			case 1105: return 89.930344440;     // 90Ru
			case 1106: return 90.926741924;     // 91Ru
			case 1107: return 91.920234429;     // 92Ru
			case 1108: return 92.917104422;     // 93Ru
			case 1109: return 93.911342934;     // 94Ru
			case 1110: return 94.91040610;      // 95Ru
			case 1111: return 95.9075902549;    // 96Ru
			case 1112: return 96.907547130;     // 97Ru
			case 1113: return 97.905286869;     // 98Ru
			case 1114: return 98.905934111;     // 99Ru
			case 1115: return 99.904214311;     // 100Ru
			case 1116: return 100.905576912;    // 101Ru
			case 1117: return 101.904344112;    // 102Ru
			case 1118: return 102.906318612;    // 103Ru
			case 1119: return 103.905427528;    // 104Ru
			case 1120: return 104.907747628;    // 105Ru
			case 1121: return 105.907329158;    // 106Ru
			case 1122: return 106.909972093;    // 107Ru
			case 1123: return 107.910188093;    // 108Ru
			case 1124: return 108.913326096;    // 109Ru
			case 1125: return 109.914040796;    // 110Ru
			case 1126: return 110.91757010;     // 111Ru
			case 1127: return 111.91880910;     // 112Ru
			case 1128: return 112.92284439;     // 113Ru
			case 1129: return 113.924613638;    // 114Ru
			case 1130: return 114.92882071;     // 115Ru
			case 1131: return 115.931219240;    // 116Ru
			case 1132: return 116.9361063;      // 117Ru
			case 1133: return 117.9385332;      // 118Ru
			case 1134: return 118.9435732;      // 119Ru
			case 1135: return 119.9463143;      // 120Ru
			case 1136: return 120.9516443;      // 121Ru
			case 1137: return 121.9544754;      // 122Ru
			case 1138: return 122.9598954;      // 123Ru
			case 1139: return 123.9630564;      // 124Ru
			case 1140: return 88.9505839;       // 89Rh
			case 1141: return 89.9442243;       // 90Rh
			case 1142: return 90.9368843;       // 91Rh
			case 1143: return 91.932367747;     // 92Rh
			case 1144: return 92.925912828;     // 93Rh
			case 1145: return 93.921730536;     // 94Rh
			case 1146: return 94.915897942;     // 95Rh
			case 1147: return 95.91445311;      // 96Rh
			case 1148: return 96.91132938;      // 97Rh
			case 1149: return 97.91070813;      // 98Rh
			case 1150: return 98.908128273;     // 99Rh
			case 1151: return 99.90811719;      // 100Rh
			case 1152: return 100.906160663;    // 101Rh
			case 1153: return 101.906837450;    // 102Rh
			case 1154: return 102.905498026;    // 103Rh
			case 1155: return 103.906649226;    // 104Rh
			case 1156: return 104.905688527;    // 105Rh
			case 1157: return 105.907286858;    // 106Rh
			case 1158: return 106.90674813;     // 107Rh
			case 1159: return 107.90871415;     // 108Rh
			case 1160: return 108.908748843;    // 109Rh
			case 1161: return 109.91107919;     // 110Rh
			case 1162: return 110.911642374;    // 111Rh
			case 1163: return 111.91440347;     // 112Rh
			case 1164: return 112.915439377;    // 113Rh
			case 1165: return 113.91871877;     // 114Rh
			case 1166: return 114.920311678;    // 115Rh
			case 1167: return 115.92405976;     // 116Rh
			case 1168: return 116.926035495;    // 117Rh
			case 1169: return 117.93034026;     // 118Rh
			case 1170: return 118.93255710;     // 119Rh
			case 1171: return 119.9368621;      // 120Rh
			case 1172: return 120.9394232;      // 121Rh
			case 1173: return 121.9439932;      // 122Rh
			case 1174: return 122.9468543;      // 123Rh
			case 1175: return 123.9515143;      // 124Rh
			case 1176: return 124.9546954;      // 125Rh
			case 1177: return 125.9594654;      // 126Rh
			case 1178: return 90.9503254;       // 91Pd
			case 1179: return 91.9408854;       // 92Pd
			case 1180: return 92.9365143;       // 93Pd
			case 1181: return 93.929037646;     // 94Pd
			case 1182: return 94.924889833;     // 95Pd
			case 1183: return 95.918215145;     // 96Pd
			case 1184: return 96.916472052;     // 97Pd
			case 1185: return 97.912698351;     // 98Pd
			case 1186: return 98.911774854;     // 99Pd
			case 1187: return 99.90850519;      // 100Pd
			case 1188: return 100.908286449;    // 101Pd
			case 1189: return 101.905602228;    // 102Pd
			case 1190: return 102.906080927;    // 103Pd
			case 1191: return 103.904030514;    // 104Pd
			case 1192: return 104.905079612;    // 105Pd
			case 1193: return 105.903480412;    // 106Pd
			case 1194: return 106.905128213;    // 107Pd
			case 1195: return 107.903891612;    // 108Pd
			case 1196: return 108.905950412;    // 109Pd
			case 1197: return 109.9051722075;   // 110Pd
			case 1198: return 110.9076896886;   // 111Pd
			case 1199: return 111.907329770;    // 112Pd
			case 1200: return 112.910261075;    // 113Pd
			case 1201: return 113.910368675;    // 114Pd
			case 1202: return 114.91365915;     // 115Pd
			case 1203: return 115.914297077;    // 116Pd
			case 1204: return 116.917954778;    // 117Pd
			case 1205: return 117.919066727;    // 118Pd
			case 1206: return 118.923340289;    // 119Pd
			case 1207: return 119.924551125;    // 120Pd
			case 1208: return 120.928950336;    // 121Pd
			case 1209: return 121.93063221;     // 122Pd
			case 1210: return 122.9351421;      // 123Pd
			case 1211: return 123.9371432;      // 124Pd
			case 1212: return 124.9417943;      // 125Pd
			case 1213: return 125.9441654;      // 126Pd
			case 1214: return 126.9490754;      // 127Pd
			case 1215: return 127.9518364;      // 128Pd
			case 1216: return 92.9503354;       // 93Ag
			case 1217: return 93.9437369;       // 94Ag
			case 1218: return 94.9360243;       // 95Ag
			case 1219: return 95.93074497;      // 96Ag
			case 1220: return 96.9239712;       // 97Ag
			case 1221: return 97.92156035;      // 98Ag
			case 1222: return 98.917645867;     // 99Ag
			case 1223: return 99.916115454;     // 100Ag
			case 1224: return 100.912684052;    // 101Ag
			case 1225: return 101.911704788;    // 102Ag
			case 1226: return 102.908963141;    // 103Ag
			case 1227: return 103.908623945;    // 104Ag
			case 1228: return 104.906525649;    // 105Ag
			case 1229: return 105.906663632;    // 106Ag
			case 1230: return 106.905091626;    // 107Ag
			case 1231: return 107.905950326;    // 108Ag
			case 1232: return 108.904755314;    // 109Ag
			case 1233: return 109.906110214;    // 110Ag
			case 1234: return 110.905295916;    // 111Ag
			case 1235: return 111.907048626;    // 112Ag
			case 1236: return 112.90657318;     // 113Ag
			case 1237: return 113.908823049;    // 114Ag
			case 1238: return 114.90876720;     // 115Ag
			case 1239: return 115.911386835;    // 116Ag
			case 1240: return 116.91177415;     // 117Ag
			case 1241: return 117.914595527;    // 118Ag
			case 1242: return 118.91557016;     // 119Ag
			case 1243: return 119.918784848;    // 120Ag
			case 1244: return 120.92012513;     // 121Ag
			case 1245: return 121.92366441;     // 122Ag
			case 1246: return 122.92533733;     // 123Ag
			case 1247: return 123.9289327;      // 124Ag
			case 1248: return 124.9310564;      // 125Ag
			case 1249: return 125.9347521;      // 126Ag
			case 1250: return 126.9371121;      // 127Ag
			case 1251: return 127.9410632;      // 128Ag
			case 1252: return 128.9439532;      // 129Ag
			case 1253: return 129.9507036;      // 130Ag
			case 1254: return 94.9499454;       // 95Cd
			case 1255: return 95.9403443;       // 96Cd
			case 1256: return 96.9351032;       // 97Cd
			case 1257: return 97.92738956;      // 98Cd
			case 1258: return 98.924925817;     // 99Cd
			case 1259: return 99.920348818;     // 100Cd
			case 1260: return 100.918586216;    // 101Cd
			case 1261: return 101.914482018;    // 102Cd
			case 1262: return 102.913416519;    // 103Cd
			case 1263: return 103.909856418;    // 104Cd
			case 1264: return 104.909463915;    // 105Cd
			case 1265: return 105.906459912;    // 106Cd
			case 1266: return 106.906612118;    // 107Cd
			case 1267: return 107.904183412;    // 108Cd
			case 1268: return 108.904986717;    // 109Cd
			case 1269: return 109.9030066161;   // 110Cd
			case 1270: return 110.9041828761;   // 111Cd
			case 1271: return 111.9027628760;   // 112Cd
			case 1272: return 112.9044081345;   // 113Cd
			case 1273: return 113.9033650943;   // 114Cd
			case 1274: return 114.9054375177;   // 115Cd
			case 1275: return 115.9047631517;   // 116Cd
			case 1276: return 116.907226011;    // 117Cd
			case 1277: return 117.90692221;     // 118Cd
			case 1278: return 118.90984740;     // 119Cd
			case 1279: return 119.909868140;    // 120Cd
			case 1280: return 120.912963721;    // 121Cd
			case 1281: return 121.913459125;    // 122Cd
			case 1282: return 122.916892529;    // 123Cd
			case 1283: return 123.917657432;    // 124Cd
			case 1284: return 124.921257631;    // 125Cd
			case 1285: return 125.922429127;    // 126Cd
			case 1286: return 126.92647214;     // 127Cd
			case 1287: return 127.927812978;    // 128Cd
			case 1288: return 128.9318221;      // 129Cd
			case 1289: return 129.9339418;      // 130Cd
			case 1290: return 130.9406021;      // 131Cd
			case 1291: return 131.9460421;      // 132Cd
			case 1292: return 132.9528532;      // 133Cd
			case 1293: return 96.9493454;       // 97In
			case 1294: return 97.9421421;       // 98In
			case 1295: return 98.9341121;       // 99In
			case 1296: return 99.9309620;       // 100In
			case 1297: return 100.9263432;      // 101In
			case 1298: return 101.924107149;    // 102In
			case 1299: return 102.919881998;    // 103In
			case 1300: return 103.918214562;    // 104In
			case 1301: return 104.91450211;     // 105In
			case 1302: return 105.91346413;     // 106In
			case 1303: return 106.91029012;     // 107In
			case 1304: return 107.909693593;    // 108In
			case 1305: return 108.907151443;    // 109In
			case 1306: return 109.90717012;     // 110In
			case 1307: return 110.905108538;    // 111In
			case 1308: return 111.905537746;    // 112In
			case 1309: return 112.9040618491;   // 113In
			case 1310: return 113.9049179194;   // 114In
			case 1311: return 114.90387877612;  // 115In
			case 1312: return 115.9052599924;   // 116In
			case 1313: return 116.904515752;    // 117In
			case 1314: return 117.906356683;    // 118In
			case 1315: return 118.905850778;    // 119In
			case 1316: return 119.90796743;     // 120In
			case 1317: return 120.90785129;     // 121In
			case 1318: return 121.91028154;     // 122In
			case 1319: return 122.91043421;     // 123In
			case 1320: return 123.91318233;     // 124In
			case 1321: return 124.91360529;     // 125In
			case 1322: return 125.91650729;     // 126In
			case 1323: return 126.91744623;     // 127In
			case 1324: return 127.9204016;      // 128In
			case 1325: return 128.921805329;    // 129In
			case 1326: return 129.92497741;     // 130In
			case 1327: return 130.926971529;    // 131In
			case 1328: return 131.93300164;     // 132In
			case 1329: return 132.9383121;      // 133In
			case 1330: return 133.9445432;      // 134In
			case 1331: return 134.9500543;      // 135In
			case 1332: return 98.9485354;       // 99Sn
			case 1333: return 99.9385032;       // 100Sn
			case 1334: return 100.9352632;      // 101Sn
			case 1335: return 101.9302911;      // 102Sn
			case 1336: return 102.92810576;     // 103Sn
			case 1337: return 103.923105262;    // 104Sn
			case 1338: return 104.921268443;    // 105Sn
			case 1339: return 105.916957455;    // 106Sn
			case 1340: return 106.915713757;    // 107Sn
			case 1341: return 107.911894358;    // 108Sn
			case 1342: return 108.911292185;    // 109Sn
			case 1343: return 109.90784515;     // 110Sn
			case 1344: return 110.907740158;    // 111Sn
			case 1345: return 111.9048238761;   // 112Sn
			case 1346: return 112.905175718;    // 113Sn
			case 1347: return 113.902782710;    // 114Sn
			case 1348: return 114.90334469916;  // 115Sn
			case 1349: return 115.9017428010;   // 116Sn
			case 1350: return 116.9029539852;   // 117Sn
			case 1351: return 117.9016065754;   // 118Sn
			case 1352: return 118.9033111778;   // 119Sn
			case 1353: return 119.9022016397;   // 120Sn
			case 1354: return 120.904242610;    // 121Sn
			case 1355: return 121.903443826;    // 122Sn
			case 1356: return 122.905725226;    // 123Sn
			case 1357: return 123.905276611;    // 124Sn
			case 1358: return 124.907786411;    // 125Sn
			case 1359: return 125.90765911;     // 126Sn
			case 1360: return 126.91039011;     // 127Sn
			case 1361: return 127.91050719;     // 128Sn
			case 1362: return 128.91346521;     // 129Sn
			case 1363: return 129.913973823;    // 130Sn
			case 1364: return 130.917045065;    // 131Sn
			case 1365: return 131.917826731;    // 132Sn
			case 1366: return 132.923913426;    // 133Sn
			case 1367: return 133.928682135;    // 134Sn
			case 1368: return 134.934908633;    // 135Sn
			case 1369: return 135.9399943;      // 136Sn
			case 1370: return 136.9465554;      // 137Sn
			case 1371: return 137.9518464;      // 138Sn
			case 1372: return 102.9396932;      // 103Sb
			case 1373: return 103.9364813;      // 104Sb
			case 1374: return 104.93127623;     // 105Sb
			case 1375: return 105.928638080;    // 106Sb
			case 1376: return 106.924150645;    // 107Sb
			case 1377: return 107.922226759;    // 108Sb
			case 1378: return 108.918141157;    // 109Sb
			case 1379: return 109.916854364;    // 110Sb
			case 1380: return 110.913218295;    // 111Sb
			case 1381: return 111.91240019;     // 112Sb
			case 1382: return 112.90937518;     // 113Sb
			case 1383: return 113.90929023;     // 114Sb
			case 1384: return 114.90659817;     // 115Sb
			case 1385: return 115.906793155;    // 116Sb
			case 1386: return 116.904841591;    // 117Sb
			case 1387: return 117.905532132;    // 118Sb
			case 1388: return 118.903945583;    // 119Sb
			case 1389: return 119.905079477;    // 120Sb
			case 1390: return 120.903812030;    // 121Sb
			case 1391: return 121.905169930;    // 122Sb
			case 1392: return 122.904213223;    // 123Sb
			case 1393: return 123.905935023;    // 124Sb
			case 1394: return 124.905253028;    // 125Sb
			case 1395: return 125.90725334;     // 126Sb
			case 1396: return 126.906924355;    // 127Sb
			case 1397: return 127.90914621;     // 128Sb
			case 1398: return 128.90914723;     // 129Sb
			case 1399: return 129.91166215;     // 130Sb
			case 1400: return 130.911988823;    // 131Sb
			case 1401: return 131.914507729;    // 132Sb
			case 1402: return 132.915273234;    // 133Sb
			case 1403: return 133.920535718;    // 134Sb
			case 1404: return 134.925185131;    // 135Sb
			case 1405: return 135.930745968;    // 136Sb
			case 1406: return 136.9355532;      // 137Sb
			case 1407: return 137.9414532;      // 138Sb
			case 1408: return 138.9465543;      // 139Sb
			case 1409: return 139.9528364;      // 140Sb
			case 1410: return 104.9433032;      // 105Te
			case 1411: return 105.9375011;      // 106Te
			case 1412: return 106.93501276;     // 107Te
			case 1413: return 107.929380558;    // 108Te
			case 1414: return 108.927304547;    // 109Te
			case 1415: return 109.922458171;    // 110Te
			case 1416: return 110.921000669;    // 111Te
			case 1417: return 111.916727990;    // 112Te
			case 1418: return 112.91589130;     // 113Te
			case 1419: return 113.91208930;     // 114Te
			case 1420: return 114.91190230;     // 115Te
			case 1421: return 115.90846030;     // 116Te
			case 1422: return 116.90864614;     // 117Te
			case 1423: return 117.90585420;     // 118Te
			case 1424: return 118.906407185;    // 119Te
			case 1425: return 119.904059333;    // 120Te
			case 1426: return 120.90494428;     // 121Te
			case 1427: return 121.903043516;    // 122Te
			case 1428: return 122.904269816;    // 123Te
			case 1429: return 123.902817116;    // 124Te
			case 1430: return 124.904429916;    // 125Te
			case 1431: return 125.903310916;    // 126Te
			case 1432: return 126.905225716;    // 127Te
			case 1433: return 127.9044612893;   // 128Te
			case 1434: return 128.9065964693;   // 129Te
			case 1435: return 129.90622274812;  // 130Te
			case 1436: return 130.90852221365;  // 131Te
			case 1437: return 131.908546737;    // 132Te
			case 1438: return 132.910968839;    // 133Te
			case 1439: return 133.911394030;    // 134Te
			case 1440: return 134.916555729;    // 135Te
			case 1441: return 135.920100626;    // 136Te
			case 1442: return 136.925598927;    // 137Te
			case 1443: return 137.929472247;    // 138Te
			case 1444: return 138.935367238;    // 139Te
			case 1445: return 139.93949930;     // 140Te
			case 1446: return 140.9458043;      // 141Te
			case 1447: return 141.9502254;      // 142Te
			case 1448: return 142.9567654;      // 143Te
			case 1449: return 106.9467832;      // 107I
			case 1450: return 107.9434814;      // 108I
			case 1451: return 108.938085361;    // 109I
			case 1452: return 109.93508954;     // 110I
			case 1453: return 110.930269251;    // 111I
			case 1454: return 111.92800511;     // 112I
			case 1455: return 112.923650186;    // 113I
			case 1456: return 113.9218532;      // 114I
			case 1457: return 114.91804831;     // 115I
			case 1458: return 115.9168110;      // 116I
			case 1459: return 116.91364828;     // 117I
			case 1460: return 117.91307421;     // 118I
			case 1461: return 118.91007430;     // 119I
			case 1462: return 119.91008716;     // 120I
			case 1463: return 120.907405158;    // 121I
			case 1464: return 121.907588856;    // 122I
			case 1465: return 122.905588540;    // 123I
			case 1466: return 123.906209026;    // 124I
			case 1467: return 124.904629416;    // 125I
			case 1468: return 125.905623341;    // 126I
			case 1469: return 126.904471939;    // 127I
			case 1470: return 127.905808639;    // 128I
			case 1471: return 128.904983734;    // 129I
			case 1472: return 129.906670234;    // 130I
			case 1473: return 130.9061263069;   // 131I
			case 1474: return 131.907993544;    // 132I
			case 1475: return 132.907797050;    // 133I
			case 1476: return 133.909758859;    // 134I
			case 1477: return 134.910048858;    // 135I
			case 1478: return 135.91460415;     // 136I
			case 1479: return 136.918028290;    // 137I
			case 1480: return 137.922726464;    // 138I
			case 1481: return 138.92650631;     // 139I
			case 1482: return 139.9317320;      // 140I
			case 1483: return 140.9356921;      // 141I
			case 1484: return 141.9412040;      // 142I
			case 1485: return 142.9456532;      // 143I
			case 1486: return 143.9513943;      // 144I
			case 1487: return 144.9560554;      // 145I
			case 1488: return 108.9504332;      // 109Xe
			case 1489: return 109.9442611;      // 110Xe
			case 1490: return 110.94160793;     // 111Xe
			case 1491: return 111.935559089;    // 112Xe
			case 1492: return 112.933221773;    // 113Xe
			case 1493: return 113.92798012;     // 114Xe
			case 1494: return 114.92629413;     // 115Xe
			case 1495: return 115.92158114;     // 116Xe
			case 1496: return 116.92035911;     // 117Xe
			case 1497: return 117.91617911;     // 118Xe
			case 1498: return 118.91541111;     // 119Xe
			case 1499: return 119.91178413;     // 120Xe
			case 1500: return 120.91145311;     // 121Xe
			case 1501: return 121.90836812;     // 122Xe
			case 1502: return 122.90848210;     // 123Xe
			case 1503: return 123.905892019;    // 124Xe
			case 1504: return 124.906394420;    // 125Xe
			case 1505: return 125.904298338;    // 126Xe
			case 1506: return 126.905182944;    // 127Xe
			case 1507: return 127.903531011;    // 128Xe
			case 1508: return 128.904780861160; // 129Xe
			case 1509: return 129.90350934910;  // 130Xe
			case 1510: return 130.9050840624;   // 131Xe
			case 1511: return 131.904155085656; // 132Xe
			case 1512: return 132.905910826;    // 133Xe
			case 1513: return 133.9053946690;   // 134Xe
			case 1514: return 134.907227845;    // 135Xe
			case 1515: return 135.90721448411;  // 136Xe
			case 1516: return 136.9115577811;   // 137Xe
			case 1517: return 137.914146330;    // 138Xe
			case 1518: return 138.918792223;    // 139Xe
			case 1519: return 139.921645825;    // 140Xe
			case 1520: return 140.926787231;    // 141Xe
			case 1521: return 141.929973129;    // 142Xe
			case 1522: return 142.935369650;    // 143Xe
			case 1523: return 143.938945157;    // 144Xe
			case 1524: return 144.94472012;     // 145Xe
			case 1525: return 145.94851826;     // 146Xe
			case 1526: return 146.9542621;      // 147Xe
			case 1527: return 147.9581321;      // 148Xe
			case 1528: return 111.95030993;     // 112Cs
			case 1529: return 112.944429193;    // 113Cs
			case 1530: return 113.94129676;     // 114Cs
			case 1531: return 114.9359132;      // 115Cs
			case 1532: return 115.9333711;      // 116Cs
			case 1533: return 116.92861767;     // 117Cs
			case 1534: return 117.92656014;     // 118Cs
			case 1535: return 118.92237715;     // 119Cs
			case 1536: return 119.92067711;     // 120Cs
			case 1537: return 120.91722715;     // 121Cs
			case 1538: return 121.91610836;     // 122Cs
			case 1539: return 122.91299613;     // 123Cs
			case 1540: return 123.912257889;    // 124Cs
			case 1541: return 124.909728083;    // 125Cs
			case 1542: return 125.90944611;     // 126Cs
			case 1543: return 126.907417460;    // 127Cs
			case 1544: return 127.907748758;    // 128Cs
			case 1545: return 128.906065749;    // 129Cs
			case 1546: return 129.906709390;    // 130Cs
			case 1547: return 130.905464953;    // 131Cs
			case 1548: return 131.906433921;    // 132Cs
			case 1549: return 132.905451961080; // 133Cs
			case 1550: return 133.90671850317;  // 134Cs
			case 1551: return 134.905977011;    // 135Cs
			case 1552: return 135.907311420;    // 136Cs
			case 1553: return 136.9070892336;   // 137Cs
			case 1554: return 137.911017198;    // 138Cs
			case 1555: return 138.913363834;    // 139Cs
			case 1556: return 139.917283188;    // 140Cs
			case 1557: return 140.920045598;    // 141Cs
			case 1558: return 141.924296079;    // 142Cs
			case 1559: return 142.92734924;     // 143Cs
			case 1560: return 143.93207627;     // 144Cs
			case 1561: return 144.93552712;     // 145Cs
			case 1562: return 145.94034442;     // 146Cs
			case 1563: return 146.94415657;     // 147Cs
			case 1564: return 147.9492362;      // 148Cs
			case 1565: return 148.9530221;      // 149Cs
			case 1566: return 149.9583332;      // 150Cs
			case 1567: return 150.9625843;      // 151Cs
			case 1568: return 113.9506612;      // 114Ba
			case 1569: return 114.9473754;      // 115Ba
			case 1570: return 115.9412832;      // 116Ba
			case 1571: return 116.9381421;      // 117Ba
			case 1572: return 117.9330621;      // 118Ba
			case 1573: return 118.9306621;      // 119Ba
			case 1574: return 119.9260532;      // 120Ba
			case 1575: return 120.9240515;      // 121Ba
			case 1576: return 121.91990430;     // 122Ba
			case 1577: return 122.91878113;     // 123Ba
			case 1578: return 123.91509413;     // 124Ba
			case 1579: return 124.91447212;     // 125Ba
			case 1580: return 125.91125013;     // 126Ba
			case 1581: return 126.91109112;     // 127Ba
			case 1582: return 127.908342056;    // 128Ba
			case 1583: return 128.90868111;     // 129Ba
			case 1584: return 129.906320728;    // 130Ba
			case 1585: return 130.906941028;    // 131Ba
			case 1586: return 131.905061111;    // 132Ba
			case 1587: return 132.906007411;    // 133Ba
			case 1588: return 133.9045081830;   // 134Ba
			case 1589: return 134.9056883829;   // 135Ba
			case 1590: return 135.9045757329;   // 136Ba
			case 1591: return 136.9058271430;   // 137Ba
			case 1592: return 137.9052470031;   // 138Ba
			case 1593: return 138.9088411031;   // 139Ba
			case 1594: return 139.910605785;    // 140Ba
			case 1595: return 140.914403357;    // 141Ba
			case 1596: return 141.916432464;    // 142Ba
			case 1597: return 142.920625374;    // 143Ba
			case 1598: return 143.922954977;    // 144Ba
			case 1599: return 144.927518491;    // 145Ba
			case 1600: return 145.93028422;     // 146Ba
			case 1601: return 146.93530421;     // 147Ba
			case 1602: return 147.93817168;     // 148Ba
			case 1603: return 148.9430821;      // 149Ba
			case 1604: return 149.9460532;      // 150Ba
			case 1605: return 150.9512732;      // 151Ba
			case 1606: return 151.9548143;      // 152Ba
			case 1607: return 152.9603643;      // 153Ba
			case 1608: return 115.9563023;      // 116La
			case 1609: return 116.9499932;      // 117La
			case 1610: return 117.9467332;      // 118La
			case 1611: return 118.9409932;      // 119La
			case 1612: return 119.9380732;      // 120La
			case 1613: return 120.9331532;      // 121La
			case 1614: return 121.9307132;      // 122La
			case 1615: return 122.9263021;      // 123La
			case 1616: return 123.92457461;     // 124La
			case 1617: return 124.92081628;     // 125La
			case 1618: return 125.91951397;     // 126La
			case 1619: return 126.91637528;     // 127La
			case 1620: return 127.91559258;     // 128La
			case 1621: return 128.91269423;     // 129La
			case 1622: return 129.91236928;     // 130La
			case 1623: return 130.91007030;     // 131La
			case 1624: return 131.91011939;     // 132La
			case 1625: return 132.90821830;     // 133La
			case 1626: return 133.90851421;     // 134La
			case 1627: return 134.90698410;     // 135La
			case 1628: return 135.90763557;     // 136La
			case 1629: return 136.906450418;    // 137La
			case 1630: return 137.907114937;    // 138La
			case 1631: return 138.906356324;    // 139La
			case 1632: return 139.909480624;    // 140La
			case 1633: return 140.910966048;    // 141La
			case 1634: return 141.914090969;    // 142La
			case 1635: return 142.916079579;    // 143La
			case 1636: return 143.91964614;     // 144La
			case 1637: return 144.92180813;     // 145La
			case 1638: return 145.92587536;     // 146La
			case 1639: return 146.92841812;     // 147La
			case 1640: return 147.93267921;     // 148La
			case 1641: return 148.9353521;      // 149La
			case 1642: return 149.9394721;      // 150La
			case 1643: return 150.9423221;      // 151La
			case 1644: return 151.9468232;      // 152La
			case 1645: return 152.9503632;      // 153La
			case 1646: return 153.9551743;      // 154La
			case 1647: return 154.9590143;      // 155La
			case 1648: return 118.9527154;      // 119Ce
			case 1649: return 119.9465454;      // 120Ce
			case 1650: return 120.9433543;      // 121Ce
			case 1651: return 121.9378743;      // 122Ce
			case 1652: return 122.9352832;      // 123Ce
			case 1653: return 123.9303132;      // 124Ce
			case 1654: return 124.9284421;      // 125Ce
			case 1655: return 125.92397130;     // 126Ce
			case 1656: return 126.92272731;     // 127Ce
			case 1657: return 127.91891130;     // 128Ce
			case 1658: return 128.91810230;     // 129Ce
			case 1659: return 129.91473630;     // 130Ce
			case 1660: return 130.91442935;     // 131Ce
			case 1661: return 131.91146422;     // 132Ce
			case 1662: return 132.91152018;     // 133Ce
			case 1663: return 133.90892822;     // 134Ce
			case 1664: return 134.90916111;     // 135Ce
			case 1665: return 135.9071292141;   // 136Ce
			case 1666: return 136.9077623645;   // 137Ce
			case 1667: return 137.90599111;     // 138Ce
			case 1668: return 138.906655178;    // 139Ce
			case 1669: return 139.905443123;    // 140Ce
			case 1670: return 140.908280723;    // 141Ce
			case 1671: return 141.909250429;    // 142Ce
			case 1672: return 142.912392129;    // 143Ce
			case 1673: return 143.913652934;    // 144Ce
			case 1674: return 144.91726536;     // 145Ce
			case 1675: return 145.91880218;     // 146Ce
			case 1676: return 146.922689992;    // 147Ce
			case 1677: return 147.92442412;     // 148Ce
			case 1678: return 148.92842711;     // 149Ce
			case 1679: return 149.93038413;     // 150Ce
			case 1680: return 150.93427219;     // 151Ce
			case 1681: return 151.9366021;      // 152Ce
			case 1682: return 152.9409321;      // 153Ce
			case 1683: return 153.9438032;      // 154Ce
			case 1684: return 154.9485543;      // 155Ce
			case 1685: return 155.9518343;      // 156Ce
			case 1686: return 156.9570554;      // 157Ce
			case 1687: return 120.9553254;      // 121Pr
			case 1688: return 121.9517554;      // 122Pr
			case 1689: return 122.9459643;      // 123Pr
			case 1690: return 123.9429443;      // 124Pr
			case 1691: return 124.9377032;      // 125Pr
			case 1692: return 125.9352421;      // 126Pr
			case 1693: return 126.9307121;      // 127Pr
			case 1694: return 127.92879132;     // 128Pr
			case 1695: return 128.92509532;     // 129Pr
			case 1696: return 129.92359069;     // 130Pr
			case 1697: return 130.92023550;     // 131Pr
			case 1698: return 131.91925561;     // 132Pr
			case 1699: return 132.91633113;     // 133Pr
			case 1700: return 133.91569722;     // 134Pr
			case 1701: return 134.91311213;     // 135Pr
			case 1702: return 135.91267712;     // 136Pr
			case 1703: return 136.910679287;    // 137Pr
			case 1704: return 137.91075415;     // 138Pr
			case 1705: return 138.908940885;    // 139Pr
			case 1706: return 139.909080369;    // 140Pr
			case 1707: return 140.907657623;    // 141Pr
			case 1708: return 141.910049623;    // 142Pr
			case 1709: return 142.910822824;    // 143Pr
			case 1710: return 143.913310932;    // 144Pr
			case 1711: return 144.914518278;    // 145Pr
			case 1712: return 145.91768037;     // 146Pr
			case 1713: return 146.91900817;     // 147Pr
			case 1714: return 147.92213016;     // 148Pr
			case 1715: return 148.92373611;     // 149Pr
			case 1716: return 149.926676597;    // 150Pr
			case 1717: return 150.92830913;     // 151Pr
			case 1718: return 151.93155320;     // 152Pr
			case 1719: return 152.93390413;     // 153Pr
			case 1720: return 153.9375316;      // 154Pr
			case 1721: return 154.94050918;     // 155Pr
			case 1722: return 155.9446432;      // 156Pr
			case 1723: return 156.9478943;      // 157Pr
			case 1724: return 157.9524143;      // 158Pr
			case 1725: return 158.9558954;      // 159Pr
			case 1726: return 123.9522054;      // 124Nd
			case 1727: return 124.9489043;      // 125Nd
			case 1728: return 125.9431132;      // 126Nd
			case 1729: return 126.9403832;      // 127Nd
			case 1730: return 127.9352521;      // 128Nd
			case 1731: return 128.9331022;      // 129Nd
			case 1732: return 129.92850630;     // 130Nd
			case 1733: return 130.92724830;     // 131Nd
			case 1734: return 131.92332126;     // 132Nd
			case 1735: return 132.92234850;     // 133Nd
			case 1736: return 133.91879013;     // 134Nd
			case 1737: return 134.91818121;     // 135Nd
			case 1738: return 135.91497613;     // 136Nd
			case 1739: return 136.91456213;     // 137Nd
			case 1740: return 137.91195012;     // 138Nd
			case 1741: return 138.91195430;     // 139Nd
			case 1742: return 139.90955028;     // 140Nd
			case 1743: return 140.909614738;    // 141Nd
			case 1744: return 141.907729020;    // 142Nd
			case 1745: return 142.909820020;    // 143Nd
			case 1746: return 143.910093020;    // 144Nd
			case 1747: return 144.912579320;    // 145Nd
			case 1748: return 145.913122620;    // 146Nd
			case 1749: return 146.916106120;    // 147Nd
			case 1750: return 147.916899326;    // 148Nd
			case 1751: return 148.920154826;    // 149Nd
			case 1752: return 149.920902218;    // 150Nd
			case 1753: return 150.923840318;    // 151Nd
			case 1754: return 151.92469226;     // 152Nd
			case 1755: return 152.927718029;    // 153Nd
			case 1756: return 153.9294812;      // 154Nd
			case 1757: return 154.933135798;    // 155Nd
			case 1758: return 155.9350821;      // 156Nd
			case 1759: return 156.93938627;     // 157Nd
			case 1760: return 157.9419732;      // 158Nd
			case 1761: return 158.9465343;      // 159Nd
			case 1762: return 159.9494043;      // 160Nd
			case 1763: return 160.9542854;      // 161Nd
			case 1764: return 125.9579254;      // 126Pm
			case 1765: return 126.9519243;      // 127Pm
			case 1766: return 127.9487032;      // 128Pm
			case 1767: return 128.9432332;      // 129Pm
			case 1768: return 129.9405321;      // 130Pm
			case 1769: return 130.9356721;      // 131Pm
			case 1770: return 131.9338416;      // 132Pm
			case 1771: return 132.92978254;     // 133Pm
			case 1772: return 133.92835362;     // 134Pm
			case 1773: return 134.92482370;     // 135Pm
			case 1774: return 135.92358577;     // 136Pm
			case 1775: return 136.92048014;     // 137Pm
			case 1776: return 137.91954830;     // 138Pm
			case 1777: return 138.91680015;     // 139Pm
			case 1778: return 139.91604038;     // 140Pm
			case 1779: return 140.91355515;     // 141Pm
			case 1780: return 141.91289025;     // 142Pm
			case 1781: return 142.910938334;    // 143Pm
			case 1782: return 143.912596434;    // 144Pm
			case 1783: return 144.912755933;    // 145Pm
			case 1784: return 145.914702448;    // 146Pm
			case 1785: return 146.915145019;    // 147Pm
			case 1786: return 147.917481963;    // 148Pm
			case 1787: return 148.918342327;    // 149Pm
			case 1788: return 149.92099122;     // 150Pm
			case 1789: return 150.921217551;    // 151Pm
			case 1790: return 151.92350628;     // 152Pm
			case 1791: return 152.924156797;    // 153Pm
			case 1792: return 153.92647248;     // 154Pm
			case 1793: return 154.928137051;    // 155Pm
			case 1794: return 155.931117539;    // 156Pm
			case 1795: return 156.933121475;    // 157Pm
			case 1796: return 157.93656514;     // 158Pm
			case 1797: return 158.93928711;     // 159Pm
			case 1798: return 159.9431032;      // 160Pm
			case 1799: return 160.9460732;      // 161Pm
			case 1800: return 161.9502243;      // 162Pm
			case 1801: return 162.9535754;      // 163Pm
			case 1802: return 127.9584254;      // 128Sm
			case 1803: return 128.9547654;      // 129Sm
			case 1804: return 129.9490043;      // 130Sm
			case 1805: return 130.9461843;      // 131Sm
			case 1806: return 131.9408732;      // 132Sm
			case 1807: return 132.9385632;      // 133Sm
			case 1808: return 133.9341121;      // 134Sm
			case 1809: return 134.9325217;      // 135Sm
			case 1810: return 135.92827613;     // 136Sm
			case 1811: return 136.92697146;     // 137Sm
			case 1812: return 137.92324413;     // 138Sm
			case 1813: return 138.92229712;     // 139Sm
			case 1814: return 139.91899513;     // 140Sm
			case 1815: return 140.918481692;    // 141Sm
			case 1816: return 141.915204436;    // 142Sm
			case 1817: return 142.914635333;    // 143Sm
			case 1818: return 143.912006521;    // 144Sm
			case 1819: return 144.913417321;    // 145Sm
			case 1820: return 145.913047035;    // 146Sm
			case 1821: return 146.914904419;    // 147Sm
			case 1822: return 147.914829219;    // 148Sm
			case 1823: return 148.917192118;    // 149Sm
			case 1824: return 149.917282918;    // 150Sm
			case 1825: return 150.919939818;    // 151Sm
			case 1826: return 151.919739718;    // 152Sm
			case 1827: return 152.922104718;    // 153Sm
			case 1828: return 153.922216920;    // 154Sm
			case 1829: return 154.924647720;    // 155Sm
			case 1830: return 155.92553610;     // 156Sm
			case 1831: return 156.928418748;    // 157Sm
			case 1832: return 157.929951053;    // 158Sm
			case 1833: return 158.933217264;    // 159Sm
			case 1834: return 159.935335364;    // 160Sm
			case 1835: return 160.939160273;    // 161Sm
			case 1836: return 161.9414621;      // 162Sm
			case 1837: return 162.9455532;      // 163Sm
			case 1838: return 163.9483632;      // 164Sm
			case 1839: return 164.9529743;      // 165Sm
			case 1840: return 129.9636954;      // 130Eu
			case 1841: return 130.9578443;      // 131Eu
			case 1842: return 131.9546743;      // 132Eu
			case 1843: return 132.9492932;      // 133Eu
			case 1844: return 133.9464032;      // 134Eu
			case 1845: return 134.9418721;      // 135Eu
			case 1846: return 135.9396221;      // 136Eu
			case 1847: return 136.9354621;      // 137Eu
			case 1848: return 137.93370930;     // 138Eu
			case 1849: return 138.92979214;     // 139Eu
			case 1850: return 139.92808855;     // 140Eu
			case 1851: return 140.92493214;     // 141Eu
			case 1852: return 141.92344232;     // 142Eu
			case 1853: return 142.92029912;     // 143Eu
			case 1854: return 143.91882012;     // 144Eu
			case 1855: return 144.916272636;    // 145Eu
			case 1856: return 145.917211065;    // 146Eu
			case 1857: return 146.916752731;    // 147Eu
			case 1858: return 147.91808911;     // 148Eu
			case 1859: return 148.917937844;    // 149Eu
			case 1860: return 149.919707768;    // 150Eu
			case 1861: return 150.919857818;    // 151Eu
			case 1862: return 151.921752218;    // 152Eu
			case 1863: return 152.921238018;    // 153Eu
			case 1864: return 153.922987019;    // 154Eu
			case 1865: return 154.922901119;    // 155Eu
			case 1866: return 155.924760559;    // 156Eu
			case 1867: return 156.925433446;    // 157Eu
			case 1868: return 157.92779911;     // 158Eu
			case 1869: return 158.929100147;    // 159Eu
			case 1870: return 159.93185110;     // 160Eu
			case 1871: return 160.93366411;     // 161Eu
			case 1872: return 161.93698965;     // 162Eu
			case 1873: return 162.93919676;     // 163Eu
			case 1874: return 163.9427422;      // 164Eu
			case 1875: return 164.9455935;      // 165Eu
			case 1876: return 165.9496232;      // 166Eu
			case 1877: return 166.9528943;      // 167Eu
			case 1878: return 132.9613354;      // 133Gd
			case 1879: return 133.9556643;      // 134Gd
			case 1880: return 134.9524543;      // 135Gd
			case 1881: return 135.9473032;      // 136Gd
			case 1882: return 136.9450232;      // 137Gd
			case 1883: return 137.9402521;      // 138Gd
			case 1884: return 138.9381321;      // 139Gd
			case 1885: return 139.93367430;     // 140Gd
			case 1886: return 140.93212621;     // 141Gd
			case 1887: return 141.92811630;     // 142Gd
			case 1888: return 142.9267522;      // 143Gd
			case 1889: return 143.92296330;     // 144Gd
			case 1890: return 144.92171321;     // 145Gd
			case 1891: return 145.918318846;    // 146Gd
			case 1892: return 146.919101425;    // 147Gd
			case 1893: return 147.918121521;    // 148Gd
			case 1894: return 148.919348138;    // 149Gd
			case 1895: return 149.918664466;    // 150Gd
			case 1896: return 150.920356035;    // 151Gd
			case 1897: return 151.919799518;    // 152Gd
			case 1898: return 152.921758018;    // 153Gd
			case 1899: return 153.920874117;    // 154Gd
			case 1900: return 154.922630517;    // 155Gd
			case 1901: return 155.922131217;    // 156Gd
			case 1902: return 156.923968617;    // 157Gd
			case 1903: return 157.924112317;    // 158Gd
			case 1904: return 158.926397017;    // 159Gd
			case 1905: return 159.927062418;    // 160Gd
			case 1906: return 160.929677521;    // 161Gd
			case 1907: return 161.930993045;    // 162Gd
			case 1908: return 162.934176990;    // 163Gd
			case 1909: return 163.9358321;      // 164Gd
			case 1910: return 164.9393632;      // 165Gd
			case 1911: return 165.9414664;      // 166Gd
			case 1912: return 166.9454543;      // 167Gd
			case 1913: return 167.9480843;      // 168Gd
			case 1914: return 168.9526054;      // 169Gd
			case 1915: return 134.9647643;      // 135Tb
			case 1916: return 135.9612954;      // 136Tb
			case 1917: return 136.9560254;      // 137Tb
			case 1918: return 137.9531232;      // 138Tb
			case 1919: return 138.9483332;      // 139Tb
			case 1920: return 139.9458186;      // 140Tb
			case 1921: return 140.9414511;      // 141Tb
			case 1922: return 141.9392875;      // 142Tb
			case 1923: return 142.93513755;     // 143Tb
			case 1924: return 143.93304530;     // 144Tb
			case 1925: return 144.9288210;      // 145Tb
			case 1926: return 145.92725348;     // 146Tb
			case 1927: return 146.924054887;    // 147Tb
			case 1928: return 147.92428214;     // 148Tb
			case 1929: return 148.923253541;    // 149Tb
			case 1930: return 149.923664980;    // 150Tb
			case 1931: return 150.923109646;    // 151Tb
			case 1932: return 151.92408343;     // 152Tb
			case 1933: return 152.923442444;    // 153Tb
			case 1934: return 153.92468549;     // 154Tb
			case 1935: return 154.92351111;     // 155Tb
			case 1936: return 155.924755243;    // 156Tb
			case 1937: return 156.924033018;    // 157Tb
			case 1938: return 157.925420920;    // 158Tb
			case 1939: return 158.925354719;    // 159Tb
			case 1940: return 159.927175619;    // 160Tb
			case 1941: return 160.927577820;    // 161Tb
			case 1942: return 161.92949539;     // 162Tb
			case 1943: return 162.930654747;    // 163Tb
			case 1944: return 163.9333611;      // 164Tb
			case 1945: return 164.9349821;      // 165Tb
			case 1946: return 165.93786075;     // 166Tb
			case 1947: return 166.9399621;      // 167Tb
			case 1948: return 167.9434032;      // 168Tb
			case 1949: return 168.9459732;      // 169Tb
			case 1950: return 169.9498443;      // 170Tb
			case 1951: return 170.9527354;      // 171Tb
			case 1952: return 137.9625043;      // 138Dy
			case 1953: return 138.9595954;      // 139Dy
			case 1954: return 139.9540254;      // 140Dy
			case 1955: return 140.9512832;      // 141Dy
			case 1956: return 141.9461978;      // 142Dy
			case 1957: return 142.94399414;     // 143Dy
			case 1958: return 143.939269577;    // 144Dy
			case 1959: return 144.937474070;    // 145Dy
			case 1960: return 145.932844572;    // 146Dy
			case 1961: return 146.931082795;    // 147Dy
			case 1962: return 147.92715710;     // 148Dy
			case 1963: return 148.92732210;     // 149Dy
			case 1964: return 149.925593348;    // 150Dy
			case 1965: return 150.926191638;    // 151Dy
			case 1966: return 151.924725351;    // 152Dy
			case 1967: return 152.925772445;    // 153Dy
			case 1968: return 153.924429380;    // 154Dy
			case 1969: return 154.92575910;     // 155Dy
			case 1970: return 155.924284717;    // 156Dy
			case 1971: return 156.925470757;    // 157Dy
			case 1972: return 157.924415931;    // 158Dy
			case 1973: return 158.925747022;    // 159Dy
			case 1974: return 159.925204620;    // 160Dy
			case 1975: return 160.926940520;    // 161Dy
			case 1976: return 161.926805620;    // 162Dy
			case 1977: return 162.928738320;    // 163Dy
			case 1978: return 163.929181920;    // 164Dy
			case 1979: return 164.931710520;    // 165Dy
			case 1980: return 165.932813921;    // 166Dy
			case 1981: return 166.93566165;     // 167Dy
			case 1982: return 167.9371315;      // 168Dy
			case 1983: return 168.9403132;      // 169Dy
			case 1984: return 169.9423921;      // 170Dy
			case 1985: return 170.9461232;      // 171Dy
			case 1986: return 171.9484632;      // 172Dy
			case 1987: return 172.9528343;      // 173Dy
			case 1988: return 139.9685954;      // 140Ho
			case 1989: return 140.9631154;      // 141Ho
			case 1990: return 141.9600154;      // 142Ho
			case 1991: return 142.9548643;      // 143Ho
			case 1992: return 143.952109791;    // 144Ho
			case 1993: return 144.947267480;    // 145Ho
			case 1994: return 145.944993571;    // 146Ho
			case 1995: return 146.940142354;    // 147Ho
			case 1996: return 147.93774490;     // 148Ho
			case 1997: return 148.93380316;     // 149Ho
			case 1998: return 149.93349815;     // 150Ho
			case 1999: return 150.931698389;    // 151Ho
			case 2000: return 151.93172414;     // 152Ho
			case 2001: return 152.930206456;    // 153Ho
			case 2002: return 153.930606889;    // 154Ho
			case 2003: return 154.92910419;     // 155Ho
			case 2004: return 155.92970664;     // 156Ho
			case 2005: return 156.92825425;     // 157Ho
			case 2006: return 157.92894629;     // 158Ho
			case 2007: return 158.927719736;    // 159Ho
			case 2008: return 159.92873716;     // 160Ho
			case 2009: return 160.927861530;    // 161Ho
			case 2010: return 161.929102339;    // 162Ho
			case 2011: return 162.928741020;    // 163Ho
			case 2012: return 163.930240325;    // 164Ho
			case 2013: return 164.930328821;    // 165Ho
			case 2014: return 165.932290921;    // 166Ho
			case 2015: return 166.933138559;    // 167Ho
			case 2016: return 167.93552232;     // 168Ho
			case 2017: return 168.93687822;     // 169Ho
			case 2018: return 169.93962554;     // 170Ho
			case 2019: return 170.9414764;      // 171Ho
			case 2020: return 171.9447321;      // 172Ho
			case 2021: return 172.9470232;      // 173Ho
			case 2022: return 173.9509532;      // 174Ho
			case 2023: return 174.9536243;      // 175Ho
			case 2024: return 141.9701054;      // 142Er
			case 2025: return 142.9666243;      // 143Er
			case 2026: return 143.9607021;      // 144Er
			case 2027: return 144.9580521;      // 145Er
			case 2028: return 145.952418472;    // 146Er
			case 2029: return 146.94996441;     // 147Er
			case 2030: return 147.94473511;     // 148Er
			case 2031: return 148.94230630;     // 149Er
			case 2032: return 149.93791618;     // 150Er
			case 2033: return 150.93744918;     // 151Er
			case 2034: return 151.93505710;     // 152Er
			case 2035: return 152.93508010;     // 153Er
			case 2036: return 153.932790855;    // 154Er
			case 2037: return 154.933215967;    // 155Er
			case 2038: return 155.93106726;     // 156Er
			case 2039: return 156.93194927;     // 157Er
			case 2040: return 157.92989327;     // 158Er
			case 2041: return 158.930691842;    // 159Er
			case 2042: return 159.92907726;     // 160Er
			case 2043: return 160.930004696;    // 161Er
			case 2044: return 161.928788420;    // 162Er
			case 2045: return 162.930040853;    // 163Er
			case 2046: return 163.929208820;    // 164Er
			case 2047: return 164.930734521;    // 165Er
			case 2048: return 165.930299522;    // 166Er
			case 2049: return 166.932054622;    // 167Er
			case 2050: return 167.932376722;    // 168Er
			case 2051: return 168.934596822;    // 169Er
			case 2052: return 169.935470226;    // 170Er
			case 2053: return 170.938035726;    // 171Er
			case 2054: return 171.939361947;    // 172Er
			case 2055: return 172.9424021;      // 173Er
			case 2056: return 173.9442332;      // 174Er
			case 2057: return 174.9477743;      // 175Er
			case 2058: return 175.9499443;      // 176Er
			case 2059: return 176.9539954;      // 177Er
			case 2060: return 143.9762843;      // 144Tm
			case 2061: return 144.9703921;      // 145Tm
			case 2062: return 145.9668421;      // 146Tm
			case 2063: return 146.961379973;    // 147Tm
			case 2064: return 147.95838411;     // 148Tm
			case 2065: return 148.9528932;      // 149Tm
			case 2066: return 149.9500921;      // 150Tm
			case 2067: return 150.94548821;     // 151Tm
			case 2068: return 151.94442279;     // 152Tm
			case 2069: return 152.94204016;     // 153Tm
			case 2070: return 153.94157015;     // 154Tm
			case 2071: return 154.93921011;     // 155Tm
			case 2072: return 155.93899216;     // 156Tm
			case 2073: return 156.93694428;     // 157Tm
			case 2074: return 157.93698027;     // 158Tm
			case 2075: return 158.93497530;     // 159Tm
			case 2076: return 159.93526337;     // 160Tm
			case 2077: return 160.93354930;     // 161Tm
			case 2078: return 161.93400228;     // 162Tm
			case 2079: return 162.932659262;    // 163Tm
			case 2080: return 163.93354426;     // 164Tm
			case 2081: return 164.932443126;    // 165Tm
			case 2082: return 165.93356113;     // 166Tm
			case 2083: return 166.932856225;    // 167Tm
			case 2084: return 167.934177427;    // 168Tm
			case 2085: return 168.934217922;    // 169Tm
			case 2086: return 169.935806022;    // 170Tm
			case 2087: return 170.936433924;    // 171Tm
			case 2088: return 171.938405562;    // 172Tm
			case 2089: return 172.939608453;    // 173Tm
			case 2090: return 173.94217348;     // 174Tm
			case 2091: return 174.94384154;     // 175Tm
			case 2092: return 175.9470011;      // 176Tm
			case 2093: return 176.9490432;      // 177Tm
			case 2094: return 177.9526443;      // 178Tm
			case 2095: return 178.9553454;      // 179Tm
			case 2096: return 147.9675864;      // 148Yb
			case 2097: return 148.9643654;      // 149Yb
			case 2098: return 149.9585243;      // 150Yb
			case 2099: return 150.9554032;      // 151Yb
			case 2100: return 151.9502717;      // 152Yb
			case 2101: return 152.9493221;      // 153Yb
			case 2102: return 153.94639619;     // 154Yb
			case 2103: return 154.94578318;     // 155Yb
			case 2104: return 155.94282511;     // 156Yb
			case 2105: return 156.94264512;     // 157Yb
			case 2106: return 157.939870586;    // 158Yb
			case 2107: return 158.94005519;     // 159Yb
			case 2108: return 159.93755717;     // 160Yb
			case 2109: return 160.93790717;     // 161Yb
			case 2110: return 161.93577417;     // 162Yb
			case 2111: return 162.93634017;     // 163Yb
			case 2112: return 163.93449517;     // 164Yb
			case 2113: return 164.93527028;     // 165Yb
			case 2114: return 165.933874778;    // 166Yb
			case 2115: return 166.934953047;    // 167Yb
			case 2116: return 167.933889622;    // 168Yb
			case 2117: return 168.935182522;    // 169Yb
			case 2118: return 169.934766422;    // 170Yb
			case 2119: return 170.936330222;    // 171Yb
			case 2120: return 171.936385922;    // 172Yb
			case 2121: return 172.938215122;    // 173Yb
			case 2122: return 173.938866422;    // 174Yb
			case 2123: return 174.941280822;    // 175Yb
			case 2124: return 175.942576424;    // 176Yb
			case 2125: return 176.945265624;    // 177Yb
			case 2126: return 177.94665111;     // 178Yb
			case 2127: return 178.9500421;      // 179Yb
			case 2128: return 179.9521232;      // 180Yb
			case 2129: return 180.9558932;      // 181Yb
			case 2130: return 149.9735554;      // 150Lu
			case 2131: return 150.9676843;      // 151Lu
			case 2132: return 151.9641221;      // 152Lu
			case 2133: return 152.9587517;      // 153Lu
			case 2134: return 153.9573622;      // 154Lu
			case 2135: return 154.95432121;     // 155Lu
			case 2136: return 155.95303379;     // 156Lu
			case 2137: return 156.95012716;     // 157Lu
			case 2138: return 157.94931616;     // 158Lu
			case 2139: return 158.94663640;     // 159Lu
			case 2140: return 159.94603361;     // 160Lu
			case 2141: return 160.94357230;     // 161Lu
			case 2142: return 161.94328381;     // 162Lu
			case 2143: return 162.94117930;     // 163Lu
			case 2144: return 163.94133930;     // 164Lu
			case 2145: return 164.93940728;     // 165Lu
			case 2146: return 165.93985932;     // 166Lu
			case 2147: return 166.93827034;     // 167Lu
			case 2148: return 167.93873642;     // 168Lu
			case 2149: return 168.937644139;    // 169Lu
			case 2150: return 169.93847818;     // 170Lu
			case 2151: return 170.937917027;    // 171Lu
			case 2152: return 171.939089130;    // 172Lu
			case 2153: return 172.938934023;    // 173Lu
			case 2154: return 173.940340923;    // 174Lu
			case 2155: return 174.940775220;    // 175Lu
			case 2156: return 175.942689720;    // 176Lu
			case 2157: return 176.943761520;    // 177Lu
			case 2158: return 177.945958029;    // 178Lu
			case 2159: return 178.947330957;    // 179Lu
			case 2160: return 179.94988876;     // 180Lu
			case 2161: return 180.9519117;      // 181Lu
			case 2162: return 181.9550421;      // 182Lu
			case 2163: return 182.95736398;     // 183Lu
			case 2164: return 183.9609132;      // 184Lu
			case 2165: return 184.9636232;      // 185Lu
			case 2166: return 152.9706954;      // 153Hf
			case 2167: return 153.9648654;      // 154Hf
			case 2168: return 154.9631132;      // 155Hf
			case 2169: return 155.9593517;      // 156Hf
			case 2170: return 156.9582421;      // 157Hf
			case 2171: return 157.95480119;     // 158Hf
			case 2172: return 158.95399618;     // 159Hf
			case 2173: return 159.95069111;     // 160Hf
			case 2174: return 160.95027824;     // 161Hf
			case 2175: return 161.947214897;    // 162Hf
			case 2176: return 162.94711327;     // 163Hf
			case 2177: return 163.94437117;     // 164Hf
			case 2178: return 164.94456730;     // 165Hf
			case 2179: return 165.94218030;     // 166Hf
			case 2180: return 166.94260030;     // 167Hf
			case 2181: return 167.94056830;     // 168Hf
			case 2182: return 168.94125930;     // 169Hf
			case 2183: return 169.93960930;     // 170Hf
			case 2184: return 170.94049231;     // 171Hf
			case 2185: return 171.93945026;     // 172Hf
			case 2186: return 172.94051330;     // 173Hf
			case 2187: return 173.940046128;    // 174Hf
			case 2188: return 174.941509229;    // 175Hf
			case 2189: return 175.941407622;    // 176Hf
			case 2190: return 176.943227720;    // 177Hf
			case 2191: return 177.943705820;    // 178Hf
			case 2192: return 178.945823220;    // 179Hf
			case 2193: return 179.946557020;    // 180Hf
			case 2194: return 180.949108320;    // 181Hf
			case 2195: return 181.950561268;    // 182Hf
			case 2196: return 182.95353032;     // 183Hf
			case 2197: return 183.95544643;     // 184Hf
			case 2198: return 184.95886298;     // 185Hf
			case 2199: return 185.96089759;     // 186Hf
			case 2200: return 186.9647732;      // 187Hf
			case 2201: return 187.9668532;      // 188Hf
			case 2202: return 188.9708432;      // 189Hf
			case 2203: return 154.9742454;      // 155Ta
			case 2204: return 155.9720332;      // 156Ta
			case 2205: return 156.9681817;      // 157Ta
			case 2206: return 157.9665422;      // 158Ta
			case 2207: return 158.96302321;     // 159Ta
			case 2208: return 159.96148879;     // 160Ta
			case 2209: return 160.95845227;     // 161Ta
			case 2210: return 161.95729456;     // 162Ta
			case 2211: return 162.95433741;     // 163Ta
			case 2212: return 163.95353430;     // 164Ta
			case 2213: return 164.95078115;     // 165Ta
			case 2214: return 165.95051230;     // 166Ta
			case 2215: return 166.94809330;     // 167Ta
			case 2216: return 167.94804730;     // 168Ta
			case 2217: return 168.94601130;     // 169Ta
			case 2218: return 169.94617530;     // 170Ta
			case 2219: return 170.94447630;     // 171Ta
			case 2220: return 171.94489530;     // 172Ta
			case 2221: return 172.94375030;     // 173Ta
			case 2222: return 173.94445430;     // 174Ta
			case 2223: return 174.94373730;     // 175Ta
			case 2224: return 175.94485733;     // 176Ta
			case 2225: return 176.944479538;    // 177Ta
			case 2226: return 177.94567856;     // 178Ta
			case 2227: return 178.945936621;    // 179Ta
			case 2228: return 179.947464824;    // 180Ta
			case 2229: return 180.947995820;    // 181Ta
			case 2230: return 181.950151920;    // 182Ta
			case 2231: return 182.951372620;    // 183Ta
			case 2232: return 183.95400828;     // 184Ta
			case 2233: return 184.95555915;     // 185Ta
			case 2234: return 185.95855164;     // 186Ta
			case 2235: return 186.96038671;     // 187Ta
			case 2236: return 187.96391671;     // 188Ta
			case 2237: return 188.9658332;      // 189Ta
			case 2238: return 189.9693921;      // 190Ta
			case 2239: return 190.9715632;      // 191Ta
			case 2240: return 191.9751443;      // 192Ta
			case 2241: return 156.9788443;      // 157W
			case 2242: return 157.9745654;      // 158W
			case 2243: return 158.9726432;      // 159W
			case 2244: return 159.9684617;      // 160W
			case 2245: return 160.9672021;      // 161W
			case 2246: return 161.96349919;     // 162W
			case 2247: return 162.96252457;     // 163W
			case 2248: return 163.95896111;     // 164W
			case 2249: return 164.95828127;     // 165W
			case 2250: return 165.95503110;     // 166W
			case 2251: return 166.95480520;     // 167W
			case 2252: return 167.95180614;     // 168W
			case 2253: return 168.95177917;     // 169W
			case 2254: return 169.94923214;     // 170W
			case 2255: return 170.94945130;     // 171W
			case 2256: return 171.94729230;     // 172W
			case 2257: return 172.94768930;     // 173W
			case 2258: return 173.94607930;     // 174W
			case 2259: return 174.94671730;     // 175W
			case 2260: return 175.94563430;     // 176W
			case 2261: return 176.94664330;     // 177W
			case 2262: return 177.94588316;     // 178W
			case 2263: return 178.94707716;     // 179W
			case 2264: return 179.946710820;    // 180W
			case 2265: return 180.948197851;    // 181W
			case 2266: return 181.9482039491;   // 182W
			case 2267: return 182.9502227590;   // 183W
			case 2268: return 183.9509309294;   // 184W
			case 2269: return 184.9534189799;   // 185W
			case 2270: return 185.954362817;    // 186W
			case 2271: return 186.957158817;    // 187W
			case 2272: return 187.958486236;    // 188W
			case 2273: return 188.96176344;     // 189W
			case 2274: return 189.96309142;     // 190W
			case 2275: return 190.96653148;     // 191W
			case 2276: return 191.9681721;      // 192W
			case 2277: return 192.9717821;      // 193W
			case 2278: return 193.9736732;      // 194W
			case 2279: return 158.9841854;      // 159Re
			case 2280: return 159.9818232;      // 160Re
			case 2281: return 160.9775717;      // 161Re
			case 2282: return 161.9758422;      // 162Re
			case 2283: return 162.97208020;     // 163Re
			case 2284: return 163.97045379;     // 164Re
			case 2285: return 164.96710327;     // 165Re
			case 2286: return 165.96576178;     // 166Re
			case 2287: return 166.96259544;     // 167Re
			case 2288: return 167.96157333;     // 168Re
			case 2289: return 168.95876612;     // 169Re
			case 2290: return 169.95822028;     // 170Re
			case 2291: return 170.95571630;     // 171Re
			case 2292: return 171.95542042;     // 172Re
			case 2293: return 172.95324330;     // 173Re
			case 2294: return 173.95311530;     // 174Re
			case 2295: return 174.95138130;     // 175Re
			case 2296: return 175.95162330;     // 176Re
			case 2297: return 176.95032830;     // 177Re
			case 2298: return 177.95098930;     // 178Re
			case 2299: return 178.94998926;     // 179Re
			case 2300: return 179.95079223;     // 180Re
			case 2301: return 180.95005814;     // 181Re
			case 2302: return 181.9512111;      // 182Re
			case 2303: return 182.950819686;    // 183Re
			case 2304: return 183.952522847;    // 184Re
			case 2305: return 184.952954513;    // 185Re
			case 2306: return 185.954985613;    // 186Re
			case 2307: return 186.955750116;    // 187Re
			case 2308: return 187.958111516;    // 188Re
			case 2309: return 188.959226089;    // 189Re
			case 2310: return 189.96174476;     // 190Re
			case 2311: return 190.96312211;     // 191Re
			case 2312: return 191.96608882;     // 192Re
			case 2313: return 192.96754141;     // 193Re
			case 2314: return 193.9707621;      // 194Re
			case 2315: return 194.9725432;      // 195Re
			case 2316: return 195.9758032;      // 196Re
			case 2317: return 196.9779932;      // 197Re
			case 2318: return 197.9816043;      // 198Re
			case 2319: return 160.9890343;      // 161Os
			case 2320: return 161.9844354;      // 162Os
			case 2321: return 162.9824132;      // 163Os
			case 2322: return 163.9780217;      // 164Os
			case 2323: return 164.9766022;      // 165Os
			case 2324: return 165.97269220;     // 166Os
			case 2325: return 166.97154978;     // 167Os
			case 2326: return 167.96780812;     // 168Os
			case 2327: return 168.96701827;     // 169Os
			case 2328: return 169.96357811;     // 170Os
			case 2329: return 170.96317419;     // 171Os
			case 2330: return 171.96001714;     // 172Os
			case 2331: return 172.95980816;     // 173Os
			case 2332: return 173.95706411;     // 174Os
			case 2333: return 174.95694513;     // 175Os
			case 2334: return 175.95480630;     // 176Os
			case 2335: return 176.95496617;     // 177Os
			case 2336: return 177.95325415;     // 178Os
			case 2337: return 178.95381718;     // 179Os
			case 2338: return 179.95237517;     // 180Os
			case 2339: return 180.95324727;     // 181Os
			case 2340: return 181.95211023;     // 182Os
			case 2341: return 182.95312553;     // 183Os
			case 2342: return 183.952488514;    // 184Os
			case 2343: return 184.954041714;    // 185Os
			case 2344: return 185.953835016;    // 186Os
			case 2345: return 186.955747416;    // 187Os
			case 2346: return 187.955835216;    // 188Os
			case 2347: return 188.958144217;    // 189Os
			case 2348: return 189.958443717;    // 190Os
			case 2349: return 190.960926417;    // 191Os
			case 2350: return 191.961477029;    // 192Os
			case 2351: return 192.964147929;    // 193Os
			case 2352: return 193.965177230;    // 194Os
			case 2353: return 194.96831865;     // 195Os
			case 2354: return 195.96964143;     // 196Os
			case 2355: return 196.9728321;      // 197Os
			case 2356: return 197.9744121;      // 198Os
			case 2357: return 198.9780121;      // 199Os
			case 2358: return 199.9798432;      // 200Os
			case 2359: return 200.9836432;      // 201Os
			case 2360: return 201.9859543;      // 202Os
			case 2361: return 163.9919134;      // 164Ir
			case 2362: return 164.9875018;      // 165Ir
			case 2363: return 165.9856622;      // 166Ir
			case 2364: return 166.98166620;     // 167Ir
			case 2365: return 167.97990780;     // 168Ir
			case 2366: return 168.97629827;     // 169Ir
			case 2367: return 169.97492295;     // 170Ir
			case 2368: return 170.97164042;     // 171Ir
			case 2369: return 171.97060735;     // 172Ir
			case 2370: return 172.96750612;     // 173Ir
			case 2371: return 173.96686130;     // 174Ir
			case 2372: return 174.96415013;     // 175Ir
			case 2373: return 175.96365022;     // 176Ir
			case 2374: return 176.96130121;     // 177Ir
			case 2375: return 177.96108221;     // 178Ir
			case 2376: return 178.95912010;     // 179Ir
			case 2377: return 179.95922923;     // 180Ir
			case 2378: return 180.95762528;     // 181Ir
			case 2379: return 181.95807623;     // 182Ir
			case 2380: return 182.95684026;     // 183Ir
			case 2381: return 183.95747630;     // 184Ir
			case 2382: return 184.95669830;     // 185Ir
			case 2383: return 185.95794418;     // 186Ir
			case 2384: return 186.95754230;     // 187Ir
			case 2385: return 187.95882810;     // 188Ir
			case 2386: return 188.95871514;     // 189Ir
			case 2387: return 189.960541221;    // 190Ir
			case 2388: return 190.960589321;    // 191Ir
			case 2389: return 191.962600221;    // 192Ir
			case 2390: return 192.962921621;    // 193Ir
			case 2391: return 193.965073521;    // 194Ir
			case 2392: return 194.965974721;    // 195Ir
			case 2393: return 195.96839741;     // 196Ir
			case 2394: return 196.96965522;     // 197Ir
			case 2395: return 197.9722821;      // 198Ir
			case 2396: return 198.97380544;     // 199Ir
			case 2397: return 199.9768021;      // 200Ir
			case 2398: return 200.9786421;      // 201Ir
			case 2399: return 201.9819932;      // 202Ir
			case 2400: return 202.9842343;      // 203Ir
			case 2401: return 203.9896043;      // 204Ir
			case 2402: return 165.9948654;      // 166Pt
			case 2403: return 166.9926933;      // 167Pt
			case 2404: return 167.9881317;      // 168Pt
			case 2405: return 168.9865722;      // 169Pt
			case 2406: return 169.98249620;     // 170Pt
			case 2407: return 170.98124578;     // 171Pt
			case 2408: return 171.97735112;     // 172Pt
			case 2409: return 172.97644360;     // 173Pt
			case 2410: return 173.97282011;     // 174Pt
			case 2411: return 174.97241019;     // 175Pt
			case 2412: return 175.96893814;     // 176Pt
			case 2413: return 176.96847016;     // 177Pt
			case 2414: return 177.96565011;     // 178Pt
			case 2415: return 178.965359086;    // 179Pt
			case 2416: return 179.96303212;     // 180Pt
			case 2417: return 180.96309816;     // 181Pt
			case 2418: return 181.96117214;     // 182Pt
			case 2419: return 182.96159717;     // 183Pt
			case 2420: return 183.95991517;     // 184Pt
			case 2421: return 184.96061428;     // 185Pt
			case 2422: return 185.95935123;     // 186Pt
			case 2423: return 186.96061726;     // 187Pt
			case 2424: return 187.959388961;    // 188Pt
			case 2425: return 188.96083112;     // 189Pt
			case 2426: return 189.959929763;    // 190Pt
			case 2427: return 190.961672953;    // 191Pt
			case 2428: return 191.961038732;    // 192Pt
			case 2429: return 192.962982421;    // 193Pt
			case 2430: return 193.962680910;    // 194Pt
			case 2431: return 194.964791710;    // 195Pt
			case 2432: return 195.9649520999;   // 196Pt
			case 2433: return 196.9673406994;   // 197Pt
			case 2434: return 197.967894923;    // 198Pt
			case 2435: return 198.970595224;    // 199Pt
			case 2436: return 199.97144322;     // 200Pt
			case 2437: return 200.97451354;     // 201Pt
			case 2438: return 201.97563927;     // 202Pt
			case 2439: return 202.9789321;      // 203Pt
			case 2440: return 203.9807621;      // 204Pt
			case 2441: return 204.9860832;      // 205Pt
			case 2442: return 205.9896632;      // 206Pt
			case 2443: return 168.9980832;      // 169Au
			case 2444: return 169.9959722;      // 170Au
			case 2445: return 170.99187622;     // 171Au
			case 2446: return 171.98994281;     // 172Au
			case 2447: return 172.98624126;     // 173Au
			case 2448: return 173.98471795;     // 174Au
			case 2449: return 174.98130442;     // 175Au
			case 2450: return 175.98025036;     // 176Au
			case 2451: return 176.97687011;     // 177Au
			case 2452: return 177.97603261;     // 178Au
			case 2453: return 178.97317413;     // 179Au
			case 2454: return 179.97252321;     // 180Au
			case 2455: return 180.97007921;     // 181Au
			case 2456: return 181.96961822;     // 182Au
			case 2457: return 182.96759110;     // 183Au
			case 2458: return 183.96745224;     // 184Au
			case 2459: return 184.96579028;     // 185Au
			case 2460: return 185.96595323;     // 186Au
			case 2461: return 186.96454324;     // 187Au
			case 2462: return 187.96534917;     // 188Au
			case 2463: return 188.96394822;     // 189Au
			case 2464: return 189.96469817;     // 190Au
			case 2465: return 190.96370240;     // 191Au
			case 2466: return 191.96481417;     // 192Au
			case 2467: return 192.964137393;    // 193Au
			case 2468: return 193.965417823;    // 194Au
			case 2469: return 194.965035215;    // 195Au
			case 2470: return 195.966569932;    // 196Au
			case 2471: return 196.9665687971;   // 197Au
			case 2472: return 197.9682424270;   // 198Au
			case 2473: return 198.9687652870;   // 199Au
			case 2474: return 199.97075629;     // 200Au
			case 2475: return 200.971657534;    // 201Au
			case 2476: return 201.97385625;     // 202Au
			case 2477: return 202.975154433;    // 203Au
			case 2478: return 203.9778322;      // 204Au
			case 2479: return 204.9798521;      // 205Au
			case 2480: return 205.9847432;      // 206Au
			case 2481: return 206.9884032;      // 207Au
			case 2482: return 207.9934532;      // 208Au
			case 2483: return 208.9973543;      // 209Au
			case 2484: return 210.0025043;      // 210Au
			case 2485: return 171.0035333;      // 171Hg
			case 2486: return 171.9988117;      // 172Hg
			case 2487: return 172.9970922;      // 173Hg
			case 2488: return 173.99286521;     // 174Hg
			case 2489: return 174.99144178;     // 175Hg
			case 2490: return 175.98736114;     // 176Hg
			case 2491: return 176.98627781;     // 177Hg
			case 2492: return 177.98248412;     // 178Hg
			case 2493: return 178.98183129;     // 179Hg
			case 2494: return 179.97826014;     // 180Hg
			case 2495: return 180.97781917;     // 181Hg
			case 2496: return 181.97468911;     // 182Hg
			case 2497: return 182.974444876;    // 183Hg
			case 2498: return 183.97171411;     // 184Hg
			case 2499: return 184.97189917;     // 185Hg
			case 2500: return 185.96936213;     // 186Hg
			case 2501: return 186.96981415;     // 187Hg
			case 2502: return 187.96756712;     // 188Hg
			case 2503: return 188.96819534;     // 189Hg
			case 2504: return 189.96632317;     // 190Hg
			case 2505: return 190.96715724;     // 191Hg
			case 2506: return 191.96563517;     // 192Hg
			case 2507: return 192.96665317;     // 193Hg
			case 2508: return 193.965449131;    // 194Hg
			case 2509: return 194.96672125;     // 195Hg
			case 2510: return 195.965832632;    // 196Hg
			case 2511: return 196.967212835;    // 197Hg
			case 2512: return 197.9667686052;   // 198Hg
			case 2513: return 198.9682806446;   // 199Hg
			case 2514: return 199.9683265947;   // 200Hg
			case 2515: return 200.9703028469;   // 201Hg
			case 2516: return 201.9706434069;   // 202Hg
			case 2517: return 202.972872818;    // 203Hg
			case 2518: return 203.9734939853;   // 204Hg
			case 2519: return 204.976073439;    // 205Hg
			case 2520: return 205.97751422;     // 206Hg
			case 2521: return 206.98230032;     // 207Hg
			case 2522: return 207.98575933;     // 208Hg
			case 2523: return 208.9907216;      // 209Hg
			case 2524: return 209.9942421;      // 210Hg
			case 2525: return 210.9993321;      // 211Hg
			case 2526: return 212.0029632;      // 212Hg
			case 2527: return 213.0082332;      // 213Hg
			case 2528: return 214.0120043;      // 214Hg
			case 2529: return 215.0174043;      // 215Hg
			case 2530: return 216.0213243;      // 216Hg
			case 2531: return 176.00062481;     // 176Tl
			case 2532: return 176.99643125;     // 177Tl
			case 2533: return 177.9948511;      // 178Tl
			case 2534: return 178.99111143;     // 179Tl
			case 2535: return 179.99005764;     // 180Tl
			case 2536: return 180.986260098;    // 181Tl
			case 2537: return 181.98571363;     // 182Tl
			case 2538: return 182.98219310;     // 183Tl
			case 2539: return 183.98188622;     // 184Tl
			case 2540: return 184.97878922;     // 185Tl
			case 2541: return 185.97865124;     // 186Tl
			case 2542: return 186.975906388;    // 187Tl
			case 2543: return 187.97602132;     // 188Tl
			case 2544: return 188.97358812;     // 189Tl
			case 2545: return 189.97382854;     // 190Tl
			case 2546: return 190.971784279;    // 191Tl
			case 2547: return 191.97222534;     // 192Tl
			case 2548: return 192.970502072;    // 193Tl
			case 2549: return 193.97108115;     // 194Tl
			case 2550: return 194.96977412;     // 195Tl
			case 2551: return 195.97048113;     // 196Tl
			case 2552: return 196.96957618;     // 197Tl
			case 2553: return 197.97048386;     // 198Tl
			case 2554: return 198.96987730;     // 199Tl
			case 2555: return 199.970963362;    // 200Tl
			case 2556: return 200.97082215;     // 201Tl
			case 2557: return 201.97210215;     // 202Tl
			case 2558: return 202.972344614;    // 203Tl
			case 2559: return 203.973863913;    // 204Tl
			case 2560: return 204.974427814;    // 205Tl
			case 2561: return 205.976110615;    // 206Tl
			case 2562: return 206.977419759;    // 207Tl
			case 2563: return 207.982019021;    // 208Tl
			case 2564: return 208.985359486;    // 209Tl
			case 2565: return 209.99007412;     // 210Tl
			case 2566: return 210.99347545;     // 211Tl
			case 2567: return 211.9983422;      // 212Tl
			case 2568: return 213.00191529;     // 213Tl
			case 2569: return 214.0069421;      // 214Tl
			case 2570: return 215.0106432;      // 215Tl
			case 2571: return 216.0158032;      // 216Tl
			case 2572: return 217.0196643;      // 217Tl
			case 2573: return 218.0247943;      // 218Tl
			case 2574: return 178.00383126;     // 178Pb
			case 2575: return 179.00220181;     // 179Pb
			case 2576: return 179.99792815;     // 180Pb
			case 2577: return 180.99665381;     // 181Pb
			case 2578: return 181.99267213;     // 182Pb
			case 2579: return 182.99187230;     // 183Pb
			case 2580: return 183.98813614;     // 184Pb
			case 2581: return 184.98761017;     // 185Pb
			case 2582: return 185.98423812;     // 186Pb
			case 2583: return 186.983910955;    // 187Pb
			case 2584: return 187.98087511;     // 188Pb
			case 2585: return 188.98080737;     // 189Pb
			case 2586: return 189.97808213;     // 190Pb
			case 2587: return 190.97827641;     // 191Pb
			case 2588: return 191.97577513;     // 192Pb
			case 2589: return 192.97617353;     // 193Pb
			case 2590: return 193.97401219;     // 194Pb
			case 2591: return 194.97454325;     // 195Pb
			case 2592: return 195.97277415;     // 196Pb
			case 2593: return 196.973431260;    // 197Pb
			case 2594: return 197.97203416;     // 198Pb
			case 2595: return 198.97291311;     // 199Pb
			case 2596: return 199.97181912;     // 200Pb
			case 2597: return 200.97288323;     // 201Pb
			case 2598: return 201.972152040;    // 202Pb
			case 2599: return 202.973391171;    // 203Pb
			case 2600: return 203.973044013;    // 204Pb
			case 2601: return 204.974482213;    // 205Pb
			case 2602: return 205.974465713;    // 206Pb
			case 2603: return 206.975897313;    // 207Pb
			case 2604: return 207.976652513;    // 208Pb
			case 2605: return 208.981090519;    // 209Pb
			case 2606: return 209.984188916;    // 210Pb
			case 2607: return 210.988737128;    // 211Pb
			case 2608: return 211.991897723;    // 212Pb
			case 2609: return 212.996562972;    // 213Pb
			case 2610: return 213.999805925;    // 214Pb
			case 2611: return 215.0047411;      // 215Pb
			case 2612: return 216.0080321;      // 216Pb
			case 2613: return 217.0131432;      // 217Pb
			case 2614: return 218.0165932;      // 218Pb
			case 2615: return 219.0217743;      // 219Pb
			case 2616: return 220.0254143;      // 220Pb
			case 2617: return 184.00127584;     // 184Bi
			case 2618: return 184.99760087;     // 185Bi
			case 2619: return 185.99664465;     // 186Bi
			case 2620: return 186.99314711;     // 187Bi
			case 2621: return 187.99228722;     // 188Bi
			case 2622: return 188.98919522;     // 189Bi
			case 2623: return 189.98862224;     // 190Bi
			case 2624: return 190.985786680;    // 191Bi
			case 2625: return 191.98546933;     // 192Bi
			case 2626: return 192.98296010;     // 193Bi
			case 2627: return 193.98278554;     // 194Bi
			case 2628: return 194.980648857;    // 195Bi
			case 2629: return 195.98066726;     // 196Bi
			case 2630: return 196.978865189;    // 197Bi
			case 2631: return 197.97920630;     // 198Bi
			case 2632: return 198.97767311;     // 199Bi
			case 2633: return 199.97813124;     // 200Bi
			case 2634: return 200.97701016;     // 201Bi
			case 2635: return 201.97773417;     // 202Bi
			case 2636: return 202.97689314;     // 203Bi
			case 2637: return 203.977836199;    // 204Bi
			case 2638: return 204.977386755;    // 205Bi
			case 2639: return 205.978499382;    // 206Bi
			case 2640: return 206.978471026;    // 207Bi
			case 2641: return 207.979742525;    // 208Bi
			case 2642: return 208.980399116;    // 209Bi
			case 2643: return 209.984120716;    // 210Bi
			case 2644: return 210.987269759;    // 211Bi
			case 2645: return 211.991286021;    // 212Bi
			case 2646: return 212.994385156;    // 213Bi
			case 2647: return 213.99871212;     // 214Bi
			case 2648: return 215.00177016;     // 215Bi
			case 2649: return 216.00630612;     // 216Bi
			case 2650: return 217.00937219;     // 217Bi
			case 2651: return 218.01418829;     // 218Bi
			case 2652: return 219.0174821;      // 219Bi
			case 2653: return 220.0223532;      // 220Bi
			case 2654: return 221.0258732;      // 221Bi
			case 2655: return 222.0307832;      // 222Bi
			case 2656: return 223.0345043;      // 223Bi
			case 2657: return 224.0394743;      // 224Bi
			case 2658: return 186.00439335;     // 186Po
			case 2659: return 187.00304134;     // 187Po
			case 2660: return 187.99941621;     // 188Po
			case 2661: return 188.99847324;     // 189Po
			case 2662: return 189.99510114;     // 190Po
			case 2663: return 190.994558576;    // 191Po
			case 2664: return 191.99133612;     // 192Po
			case 2665: return 192.99102637;     // 193Po
			case 2666: return 193.98818614;     // 194Po
			case 2667: return 194.98812641;     // 195Po
			case 2668: return 195.98552614;     // 196Po
			case 2669: return 196.98566053;     // 197Po
			case 2670: return 197.98338919;     // 198Po
			case 2671: return 198.98366725;     // 199Po
			case 2672: return 199.98179915;     // 200Po
			case 2673: return 200.982259863;    // 201Po
			case 2674: return 201.98075816;     // 202Po
			case 2675: return 202.981416193;    // 203Po
			case 2676: return 203.98031012;     // 204Po
			case 2677: return 204.98120322;     // 205Po
			case 2678: return 205.980474043;    // 206Po
			case 2679: return 206.981593872;    // 207Po
			case 2680: return 207.981246119;    // 208Po
			case 2681: return 208.982430820;    // 209Po
			case 2682: return 209.982874113;    // 210Po
			case 2683: return 210.986653614;    // 211Po
			case 2684: return 211.988868413;    // 212Po
			case 2685: return 212.992857633;    // 213Po
			case 2686: return 213.995201716;    // 214Po
			case 2687: return 214.999420127;    // 215Po
			case 2688: return 216.001915223;    // 216Po
			case 2689: return 217.006318267;    // 217Po
			case 2690: return 218.008973525;    // 218Po
			case 2691: return 219.01361417;     // 219Po
			case 2692: return 220.01638619;     // 220Po
			case 2693: return 221.02122821;     // 221Po
			case 2694: return 222.02414043;     // 222Po
			case 2695: return 223.0290721;      // 223Po
			case 2696: return 224.0321121;      // 224Po
			case 2697: return 225.0370732;      // 225Po
			case 2698: return 226.0403143;      // 226Po
			case 2699: return 227.0453943;      // 227Po
			case 2700: return 191.00414817;     // 191At
			case 2701: return 192.00315235;     // 192At
			case 2702: return 192.99992723;     // 193At
			case 2703: return 193.99923629;     // 194At
			case 2704: return 194.996268598;    // 195At
			case 2705: return 195.99580033;     // 196At
			case 2706: return 196.99318955;     // 197At
			case 2707: return 197.99278454;     // 198At
			case 2708: return 198.990527758;    // 199At
			case 2709: return 199.99035126;     // 200At
			case 2710: return 200.988417188;    // 201At
			case 2711: return 201.98863030;     // 202At
			case 2712: return 202.98694311;     // 203At
			case 2713: return 203.98725124;     // 204At
			case 2714: return 204.98607616;     // 205At
			case 2715: return 205.98665716;     // 206At
			case 2716: return 206.98580013;     // 207At
			case 2717: return 207.986613396;    // 208At
			case 2718: return 208.986170255;    // 209At
			case 2719: return 209.987147983;    // 210At
			case 2720: return 210.987496630;    // 211At
			case 2721: return 211.990737726;    // 212At
			case 2722: return 212.992937053;    // 213At
			case 2723: return 213.996372146;    // 214At
			case 2724: return 214.998652873;    // 215At
			case 2725: return 216.002423639;    // 216At
			case 2726: return 217.004719255;    // 217At
			case 2727: return 218.00869512;     // 218At
			case 2728: return 219.011161842;    // 219At
			case 2729: return 220.01543315;     // 220At
			case 2730: return 221.01801715;     // 221At
			case 2731: return 222.02249417;     // 222At
			case 2732: return 223.02515115;     // 223At
			case 2733: return 224.02974924;     // 224At
			case 2734: return 225.0326332;      // 225At
			case 2735: return 226.0371632;      // 226At
			case 2736: return 227.0402432;      // 227At
			case 2737: return 228.0447543;      // 228At
			case 2738: return 229.0481243;      // 229At
			case 2739: return 193.00970827;     // 193Rn
			case 2740: return 194.00614418;     // 194Rn
			case 2741: return 195.00542254;     // 195Rn
			case 2742: return 196.00211615;     // 196Rn
			case 2743: return 197.00158538;     // 197Rn
			case 2744: return 197.99867914;     // 198Rn
			case 2745: return 198.99839068;     // 199Rn
			case 2746: return 199.99569014;     // 200Rn
			case 2747: return 200.99562853;     // 201Rn
			case 2748: return 201.99326419;     // 202Rn
			case 2749: return 202.99338825;     // 203Rn
			case 2750: return 203.99143016;     // 204Rn
			case 2751: return 204.99171954;     // 205Rn
			case 2752: return 205.99021416;     // 206Rn
			case 2753: return 206.990730391;    // 207Rn
			case 2754: return 207.98963512;     // 208Rn
			case 2755: return 208.99041522;     // 209Rn
			case 2756: return 209.989689149;    // 210Rn
			case 2757: return 210.990601173;    // 211Rn
			case 2758: return 211.990703934;    // 212Rn
			case 2759: return 212.993883161;    // 213Rn
			case 2760: return 213.995363099;    // 214Rn
			case 2761: return 214.998745983;    // 215Rn
			case 2762: return 216.000271965;    // 216Rn
			case 2763: return 217.003928045;    // 217Rn
			case 2764: return 218.005601625;    // 218Rn
			case 2765: return 219.009480427;    // 219Rn
			case 2766: return 220.011394123;    // 220Rn
			case 2767: return 221.015537163;    // 221Rn
			case 2768: return 222.017578225;    // 222Rn
			case 2769: return 223.021889384;    // 223Rn
			case 2770: return 224.02409611;     // 224Rn
			case 2771: return 225.02848612;     // 225Rn
			case 2772: return 226.03086111;     // 226Rn
			case 2773: return 227.03530415;     // 227Rn
			case 2774: return 228.03783519;     // 228Rn
			case 2775: return 229.04225714;     // 229Rn
			case 2776: return 230.0451421;      // 230Rn
			case 2777: return 231.0498732;      // 231Rn
			case 2778: return 199.00725945;     // 199Fr
			case 2779: return 200.00658663;     // 200Fr
			case 2780: return 201.00386777;     // 201Fr
			case 2781: return 202.00332055;     // 202Fr
			case 2782: return 203.000940767;    // 203Fr
			case 2783: return 204.00065226;     // 204Fr
			case 2784: return 204.998593984;    // 205Fr
			case 2785: return 205.99866630;     // 206Fr
			case 2786: return 206.99694619;     // 207Fr
			case 2787: return 207.99713812;     // 208Fr
			case 2788: return 208.99595516;     // 209Fr
			case 2789: return 209.99642216;     // 210Fr
			case 2790: return 210.99555613;     // 211Fr
			case 2791: return 211.996225794;    // 212Fr
			case 2792: return 212.996186055;    // 213Fr
			case 2793: return 213.998971393;    // 214Fr
			case 2794: return 215.000341876;    // 215Fr
			case 2795: return 216.003189945;    // 216Fr
			case 2796: return 217.004632370;    // 217Fr
			case 2797: return 218.007578751;    // 218Fr
			case 2798: return 219.009252476;    // 219Fr
			case 2799: return 220.012327744;    // 220Fr
			case 2800: return 221.014255254;    // 221Fr
			case 2801: return 222.01755223;     // 222Fr
			case 2802: return 223.019736025;    // 223Fr
			case 2803: return 224.02339814;     // 224Fr
			case 2804: return 225.02557313;     // 225Fr
			case 2805: return 226.02956613;     // 226Fr
			case 2806: return 227.03186914;     // 227Fr
			case 2807: return 228.03582314;     // 228Fr
			case 2808: return 229.03829815;     // 229Fr
			case 2809: return 230.04241617;     // 230Fr
			case 2810: return 231.04515827;     // 231Fr
			case 2811: return 232.0493717;      // 232Fr
			case 2812: return 233.0526432;      // 233Fr
			case 2813: return 201.0127111;      // 201Ra
			case 2814: return 202.00976026;     // 202Ra
			case 2815: return 203.00930486;     // 203Ra
			case 2816: return 204.00649216;     // 204Ra
			case 2817: return 205.00626876;     // 205Ra
			case 2818: return 206.00382819;     // 206Ra
			case 2819: return 207.00379959;     // 207Ra
			case 2820: return 208.00184117;     // 208Ra
			case 2821: return 209.00199054;     // 209Ra
			case 2822: return 210.00049416;     // 210Ra
			case 2823: return 211.000893285;    // 211Ra
			case 2824: return 211.99978712;     // 212Ra
			case 2825: return 213.00038422;     // 213Ra
			case 2826: return 214.000099756;    // 214Ra
			case 2827: return 215.002720482;    // 215Ra
			case 2828: return 216.003533494;    // 216Ra
			case 2829: return 217.006320792;    // 217Ra
			case 2830: return 218.00714112;     // 218Ra
			case 2831: return 219.010085589;    // 219Ra
			case 2832: return 220.011025989;    // 220Ra
			case 2833: return 221.013917750;    // 221Ra
			case 2834: return 222.015374849;    // 222Ra
			case 2835: return 223.018502327;    // 223Ra
			case 2836: return 224.020212023;    // 224Ra
			case 2837: return 225.023611932;    // 225Ra
			case 2838: return 226.025410325;    // 226Ra
			case 2839: return 227.029178325;    // 227Ra
			case 2840: return 228.031070726;    // 228Ra
			case 2841: return 229.03494216;     // 229Ra
			case 2842: return 230.03705511;     // 230Ra
			case 2843: return 231.04102712;     // 231Ra
			case 2844: return 232.043475398;    // 232Ra
			case 2845: return 233.04758217;     // 233Ra
			case 2846: return 234.05034233;     // 234Ra
			case 2847: return 235.0549732;      // 235Ra
			case 2848: return 206.01445277;     // 206Ac
			case 2849: return 207.01196654;     // 207Ac
			case 2850: return 208.01155060;     // 208Ac
			case 2851: return 209.00949554;     // 209Ac
			case 2852: return 210.00943662;     // 210Ac
			case 2853: return 211.00773257;     // 211Ac
			case 2854: return 212.00781355;     // 212Ac
			case 2855: return 213.00660956;     // 213Ac
			case 2856: return 214.00691816;     // 214Ac
			case 2857: return 215.00647513;     // 215Ac
			case 2858: return 216.00874312;     // 216Ac
			case 2859: return 217.00934412;     // 217Ac
			case 2860: return 218.01164254;     // 218Ac
			case 2861: return 219.01242154;     // 219Ac
			case 2862: return 220.014754966;    // 220Ac
			case 2863: return 221.01559254;     // 221Ac
			case 2864: return 222.017844256;    // 222Ac
			case 2865: return 223.019137777;    // 223Ac
			case 2866: return 224.021723245;    // 224Ac
			case 2867: return 225.023230053;    // 225Ac
			case 2868: return 226.026098436;    // 226Ac
			case 2869: return 227.027752325;    // 227Ac
			case 2870: return 228.031021527;    // 228Ac
			case 2871: return 229.03295613;     // 229Ac
			case 2872: return 230.03632717;     // 230Ac
			case 2873: return 231.03839314;     // 231Ac
			case 2874: return 232.04203414;     // 232Ac
			case 2875: return 233.04434614;     // 233Ac
			case 2876: return 234.04813915;     // 234Ac
			case 2877: return 235.05084015;     // 235Ac
			case 2878: return 236.05498841;     // 236Ac
			case 2879: return 237.0582743;      // 237Ac
			case 2880: return 208.01790036;     // 208Th
			case 2881: return 209.01775393;     // 209Th
			case 2882: return 210.01509420;     // 210Th
			case 2883: return 211.01492980;     // 211Th
			case 2884: return 212.01298817;     // 212Th
			case 2885: return 213.01300976;     // 213Th
			case 2886: return 214.01150017;     // 214Th
			case 2887: return 215.011724895;    // 215Th
			case 2888: return 216.01105613;     // 216Th
			case 2889: return 217.01311722;     // 217Th
			case 2890: return 218.01327611;     // 218Th
			case 2891: return 219.01553754;     // 219Th
			case 2892: return 220.01574824;     // 220Th
			case 2893: return 221.01818410;     // 221Th
			case 2894: return 222.01846913;     // 222Th
			case 2895: return 223.020811999;    // 223Th
			case 2896: return 224.02146411;     // 224Th
			case 2897: return 225.023951455;    // 225Th
			case 2898: return 226.024903450;    // 226Th
			case 2899: return 227.027704227;    // 227Th
			case 2900: return 228.028741323;    // 228Th
			case 2901: return 229.031762730;    // 229Th
			case 2902: return 230.033134119;    // 230Th
			case 2903: return 231.036304619;    // 231Th
			case 2904: return 232.038055821;    // 232Th
			case 2905: return 233.041582321;    // 233Th
			case 2906: return 234.043601437;    // 234Th
			case 2907: return 235.04725514;     // 235Th
			case 2908: return 236.04965715;     // 236Th
			case 2909: return 237.05362917;     // 237Th
			case 2910: return 238.0565030;      // 238Th
			case 2911: return 239.0607743;      // 239Th
			case 2912: return 212.02320380;     // 212Pa
			case 2913: return 213.02110976;     // 213Pa
			case 2914: return 214.02091882;     // 214Pa
			case 2915: return 215.01918378;     // 215Pa
			case 2916: return 216.01910957;     // 216Pa
			case 2917: return 217.01832556;     // 217Pa
			case 2918: return 218.02005920;     // 218Pa
			case 2919: return 219.01990455;     // 219Pa
			case 2920: return 220.02170555;     // 220Pa
			case 2921: return 221.02187555;     // 221Pa
			case 2922: return 222.02378478;     // 222Pa
			case 2923: return 223.02396376;     // 223Pa
			case 2924: return 224.025617682;    // 224Pa
			case 2925: return 225.02613176;     // 225Pa
			case 2926: return 226.02794812;     // 226Pa
			case 2927: return 227.028805480;    // 227Pa
			case 2928: return 228.031051747;    // 228Pa
			case 2929: return 229.032097238;    // 229Pa
			case 2930: return 230.034541035;    // 230Pa
			case 2931: return 231.035884224;    // 231Pa
			case 2932: return 232.038591783;    // 232Pa
			case 2933: return 233.040247222;    // 233Pa
			case 2934: return 234.043307251;    // 234Pa
			case 2935: return 235.04539915;     // 235Pa
			case 2936: return 236.04866815;     // 236Pa
			case 2937: return 237.05102314;     // 237Pa
			case 2938: return 238.05463717;     // 238Pa
			case 2939: return 239.0572621;      // 239Pa
			case 2940: return 240.0609832;      // 240Pa
			case 2941: return 241.0640843;      // 241Pa
			case 2942: return 217.0246611;      // 217U
			case 2943: return 218.02352320;     // 218U
			case 2944: return 219.02499955;     // 219U
			case 2945: return 220.0246211;      // 220U
			case 2946: return 221.0262811;      // 221U
			case 2947: return 222.0260011;      // 222U
			case 2948: return 223.02773976;     // 223U
			case 2949: return 224.02760527;     // 224U
			case 2950: return 225.02939113;     // 225U
			case 2951: return 226.02933914;     // 226U
			case 2952: return 227.03115718;     // 227U
			case 2953: return 228.03137115;     // 228U
			case 2954: return 229.033506364;    // 229U
			case 2955: return 230.033940151;    // 230U
			case 2956: return 231.036293932;    // 231U
			case 2957: return 232.037156323;    // 232U
			case 2958: return 233.039635529;    // 233U
			case 2959: return 234.040952319;    // 234U
			case 2960: return 235.043930119;    // 235U
			case 2961: return 236.045568219;    // 236U
			case 2962: return 237.048730420;    // 237U
			case 2963: return 238.050788420;    // 238U
			case 2964: return 239.054293520;    // 239U
			case 2965: return 240.056593457;    // 240U
			case 2966: return 241.0603332;      // 241U
			case 2967: return 242.0629322;      // 242U
			case 2968: return 243.0669943;      // 243U
			case 2969: return 219.0314321;      // 219Np
			case 2970: return 220.0325421;      // 220Np
			case 2971: return 221.0320421;      // 221Np
			case 2972: return 222.0333021;      // 222Np
			case 2973: return 223.0328521;      // 223Np
			case 2974: return 224.0342221;      // 224Np
			case 2975: return 225.03391177;     // 225Np
			case 2976: return 226.03518895;     // 226Np
			case 2977: return 227.03495778;     // 227Np
			case 2978: return 228.03606754;     // 228Np
			case 2979: return 229.03626493;     // 229Np
			case 2980: return 230.03782855;     // 230Np
			case 2981: return 231.03824554;     // 231Np
			case 2982: return 232.0401111;      // 232Np
			case 2983: return 233.04074155;     // 233Np
			case 2984: return 234.042895391;    // 234Np
			case 2985: return 235.044063521;    // 235Np
			case 2986: return 236.04657054;     // 236Np
			case 2987: return 237.048173619;    // 237Np
			case 2988: return 238.050946619;    // 238Np
			case 2989: return 239.052939222;    // 239Np
			case 2990: return 240.05616518;     // 240Np
			case 2991: return 241.05825376;     // 241Np
			case 2992: return 242.0616421;      // 242Np
			case 2993: return 243.06428034;     // 243Np
			case 2994: return 244.0678532;      // 244Np
			case 2995: return 245.0708043;      // 245Np
			case 2996: return 228.03873233;     // 228Pu
			case 2997: return 229.04014455;     // 229Pu
			case 2998: return 230.03965016;     // 230Pu
			case 2999: return 231.04110228;     // 231Pu
			case 3000: return 232.04118519;     // 232Pu
			case 3001: return 233.04299854;     // 233Pu
			case 3002: return 234.043317475;    // 234Pu
			case 3003: return 235.04528622;     // 235Pu
			case 3004: return 236.046058123;    // 236Pu
			case 3005: return 237.048409824;    // 237Pu
			case 3006: return 238.049560119;    // 238Pu
			case 3007: return 239.052163619;    // 239Pu
			case 3008: return 240.053813819;    // 240Pu
			case 3009: return 241.056851719;    // 241Pu
			case 3010: return 242.058742820;    // 242Pu
			case 3011: return 243.062003634;    // 243Pu
			case 3012: return 244.064205356;    // 244Pu
			case 3013: return 245.06782615;     // 245Pu
			case 3014: return 246.07020516;     // 246Pu
			case 3015: return 247.0741921;      // 247Pu
			case 3016: return 230.0460914;      // 230Am
			case 3017: return 231.0455632;      // 231Am
			case 3018: return 232.0464532;      // 232Am
			case 3019: return 233.0464411;      // 233Am
			case 3020: return 234.0477317;      // 234Am
			case 3021: return 235.04790856;     // 235Am
			case 3022: return 236.0494312;      // 236Am
			case 3023: return 237.04999664;     // 237Am
			case 3024: return 238.05198554;     // 238Am
			case 3025: return 239.053024726;    // 239Am
			case 3026: return 240.05530015;     // 240Am
			case 3027: return 241.056829319;    // 241Am
			case 3028: return 242.059549419;    // 242Am
			case 3029: return 243.061381324;    // 243Am
			case 3030: return 244.064285122;    // 244Am
			case 3031: return 245.066454834;    // 245Am
			case 3032: return 246.06977520;     // 246Am
			case 3033: return 247.0720911;      // 247Am
			case 3034: return 248.0757522;      // 248Am
			case 3035: return 249.0784832;      // 249Am
			case 3036: return 232.0498222;      // 232Cm
			case 3037: return 233.05077077;     // 233Cm
			case 3038: return 234.05016020;     // 234Cm
			case 3039: return 235.0515422;      // 235Cm
			case 3040: return 236.05137420;     // 236Cm
			case 3041: return 237.05286976;     // 237Cm
			case 3042: return 238.05308113;     // 238Cm
			case 3043: return 239.05491058;     // 239Cm
			case 3044: return 240.055529724;    // 240Cm
			case 3045: return 241.057653223;    // 241Cm
			case 3046: return 242.058836019;    // 242Cm
			case 3047: return 243.061389322;    // 243Cm
			case 3048: return 244.062752819;    // 244Cm
			case 3049: return 245.065491522;    // 245Cm
			case 3050: return 246.067223822;    // 246Cm
			case 3051: return 247.070354147;    // 247Cm
			case 3052: return 248.072349956;    // 248Cm
			case 3053: return 249.075954856;    // 249Cm
			case 3054: return 250.07835812;     // 250Cm
			case 3055: return 251.08228624;     // 251Cm
			case 3056: return 252.0848732;      // 252Cm
			case 3057: return 234.0572715;      // 234Bk
			case 3058: return 235.0565843;      // 235Bk
			case 3059: return 236.0574843;      // 236Bk
			case 3060: return 237.0571024;      // 237Bk
			case 3061: return 238.0582027;      // 238Bk
			case 3062: return 239.0582422;      // 239Bk
			case 3063: return 240.0597616;      // 240Bk
			case 3064: return 241.0601622;      // 241Bk
			case 3065: return 242.0619822;      // 242Bk
			case 3066: return 243.063007851;    // 243Bk
			case 3067: return 244.06518116;     // 244Bk
			case 3068: return 245.066361824;    // 245Bk
			case 3069: return 246.06867364;     // 246Bk
			case 3070: return 247.070307359;    // 247Bk
			case 3071: return 248.07308876;     // 248Bk
			case 3072: return 249.074987727;    // 249Bk
			case 3073: return 250.078316742;    // 250Bk
			case 3074: return 251.08076212;     // 251Bk
			case 3075: return 252.0843122;      // 252Bk
			case 3076: return 253.0868839;      // 253Bk
			case 3077: return 254.0906032;      // 254Bk
			case 3078: return 237.06219894;     // 237Cf
			case 3079: return 238.0614932;      // 238Cf
			case 3080: return 239.0625323;      // 239Cf
			case 3081: return 240.06225620;     // 240Cf
			case 3082: return 241.0636918;      // 241Cf
			case 3083: return 242.06375414;     // 242Cf
			case 3084: return 243.0654812;      // 243Cf
			case 3085: return 244.066000831;    // 244Cf
			case 3086: return 245.068048730;    // 245Cf
			case 3087: return 246.068805522;    // 246Cf
			case 3088: return 247.07096516;     // 247Cf
			case 3089: return 248.072185157;    // 248Cf
			case 3090: return 249.074853923;    // 249Cf
			case 3091: return 250.076406222;    // 250Cf
			case 3092: return 251.079588648;    // 251Cf
			case 3093: return 252.081627256;    // 252Cf
			case 3094: return 253.085134567;    // 253Cf
			case 3095: return 254.08732413;     // 254Cf
			case 3096: return 255.0910522;      // 255Cf
			case 3097: return 256.0934434;      // 256Cf
			case 3098: return 239.0682332;      // 239Es
			case 3099: return 240.0689243;      // 240Es
			case 3100: return 241.0685624;      // 241Es
			case 3101: return 242.0695728;      // 242Es
			case 3102: return 243.0695122;      // 243Es
			case 3103: return 244.0708820;      // 244Es
			case 3104: return 245.0712522;      // 245Es
			case 3105: return 246.0729024;      // 246Es
			case 3106: return 247.07362221;     // 247Es
			case 3107: return 248.07547156;     // 248Es
			case 3108: return 249.07641132;     // 249Es
			case 3109: return 250.0786111;      // 250Es
			case 3110: return 251.079993667;    // 251Es
			case 3111: return 252.08298054;     // 252Es
			case 3112: return 253.084825727;    // 253Es
			case 3113: return 254.088022245;    // 254Es
			case 3114: return 255.09027512;     // 255Es
			case 3115: return 256.0936011;      // 256Es
			case 3116: return 257.0959844;      // 257Es
			case 3117: return 258.0995232;      // 258Es
			case 3118: return 241.0742132;      // 241Fm
			case 3119: return 242.0734343;      // 242Fm
			case 3120: return 243.0744623;      // 243Fm
			case 3121: return 244.0740422;      // 244Fm
			case 3122: return 245.0753521;      // 245Fm
			case 3123: return 246.07535017;     // 246Fm
			case 3124: return 247.0769412;      // 247Fm
			case 3125: return 248.077186592;    // 248Fm
			case 3126: return 249.078927568;    // 249Fm
			case 3127: return 250.079521086;    // 250Fm
			case 3128: return 251.08154016;     // 251Fm
			case 3129: return 252.082467161;    // 252Fm
			case 3130: return 253.085184637;    // 253Fm
			case 3131: return 254.086854430;    // 254Fm
			case 3132: return 255.089964052;    // 255Fm
			case 3133: return 256.091774578;    // 256Fm
			case 3134: return 257.095106169;    // 257Fm
			case 3135: return 258.0970822;      // 258Fm
			case 3136: return 259.1006030;      // 259Fm
			case 3137: return 260.1028155;      // 260Fm
			case 3138: return 245.0808133;      // 245Md
			case 3139: return 246.0817128;      // 246Md
			case 3140: return 247.0815222;      // 247Md
			case 3141: return 248.0828226;      // 248Md
			case 3142: return 249.0829122;      // 249Md
			case 3143: return 250.0844132;      // 250Md
			case 3144: return 251.08477420;     // 251Md
			case 3145: return 252.0864314;      // 252Md
			case 3146: return 253.08714434;     // 253Md
			case 3147: return 254.0895911;      // 254Md
			case 3148: return 255.091084173;    // 255Md
			case 3149: return 256.0938913;      // 256Md
			case 3150: return 257.095542429;    // 257Md
			case 3151: return 258.098431550;    // 258Md
			case 3152: return 259.1005122;      // 259Md
			case 3153: return 260.1036534;      // 260Md
			case 3154: return 261.1058362;      // 261Md
			case 3155: return 262.1091045;      // 262Md
			case 3156: return 248.0865524;      // 248No
			case 3157: return 249.0878030;      // 249No
			case 3158: return 250.0875622;      // 250No
			case 3159: return 251.0889412;      // 251No
			case 3160: return 252.08896710;     // 252No
			case 3161: return 253.090564175;    // 253No
			case 3162: return 254.09095611;     // 254No
			case 3163: return 255.09319116;     // 255No
			case 3164: return 256.094282984;    // 256No
			case 3165: return 257.096887874;    // 257No
			case 3166: return 258.0982111;      // 258No
			case 3167: return 259.1010311;      // 259No
			case 3168: return 260.1026422;      // 260No
			case 3169: return 261.1057022;      // 261No
			case 3170: return 262.1074639;      // 262No
			case 3171: return 263.1107153;      // 263No
			case 3172: return 264.1127370;      // 264No
			case 3173: return 251.0941832;      // 251Lr
			case 3174: return 252.0952626;      // 252Lr
			case 3175: return 253.0950922;      // 253Lr
			case 3176: return 254.0964832;      // 254Lr
			case 3177: return 255.09656219;     // 255Lr
			case 3178: return 256.09849489;     // 256Lr
			case 3179: return 257.09941847;     // 257Lr
			case 3180: return 258.1017611;      // 258Lr
			case 3181: return 259.10290276;     // 259Lr
			case 3182: return 260.1055013;      // 260Lr
			case 3183: return 261.1068822;      // 261Lr
			case 3184: return 262.1096122;      // 262Lr
			case 3185: return 263.1113630;      // 263Lr
			case 3186: return 264.1142047;      // 264Lr
			case 3187: return 265.1161965;      // 265Lr
			case 3188: return 266.1198356;      // 266Lr
			case 3189: return 253.1004444;      // 253Rf
			case 3190: return 254.1000530;      // 254Rf
			case 3191: return 255.1012712;      // 255Rf
			case 3192: return 256.10115219;     // 256Rf
			case 3193: return 257.10291812;     // 257Rf
			case 3194: return 258.10342834;     // 258Rf
			case 3195: return 259.10559678;     // 259Rf
			case 3196: return 260.1064422;      // 260Rf
			case 3197: return 261.10877354;     // 261Rf
			case 3198: return 262.1099224;      // 262Rf
			case 3199: return 263.1124920;      // 263Rf
			case 3200: return 264.1138839;      // 264Rf
			case 3201: return 265.1166839;      // 265Rf
			case 3202: return 266.1181750;      // 266Rf
			case 3203: return 267.1217962;      // 267Rf
			case 3204: return 268.1239777;      // 268Rf
			case 3205: return 255.1070745;      // 255Db
			case 3206: return 256.1078926;      // 256Db
			case 3207: return 257.1075822;      // 257Db
			case 3208: return 258.1092833;      // 258Db
			case 3209: return 259.10949257;     // 259Db
			case 3210: return 260.1113010;      // 260Db
			case 3211: return 261.1119212;      // 261Db
			case 3212: return 262.1140715;      // 262Db
			case 3213: return 263.1149918;      // 263Db
			case 3214: return 264.1174125;      // 264Db
			case 3215: return 265.1186124;      // 265Db
			case 3216: return 266.1210330;      // 266Db
			case 3217: return 267.1224744;      // 267Db
			case 3218: return 268.1256757;      // 268Db
			case 3219: return 269.1279173;      // 269Db
			case 3220: return 270.1313664;      // 270Db
			case 3221: return 258.1129844;      // 258Sg
			case 3222: return 259.1144013;      // 259Sg
			case 3223: return 260.11438422;     // 260Sg
			case 3224: return 261.11594920;     // 261Sg
			case 3225: return 262.11633738;     // 262Sg
			case 3226: return 263.1182910;      // 263Sg
			case 3227: return 264.1189330;      // 264Sg
			case 3228: return 265.1210913;      // 265Sg
			case 3229: return 266.1219826;      // 266Sg
			case 3230: return 267.1243630;      // 267Sg
			case 3231: return 268.1253950;      // 268Sg
			case 3232: return 269.1286339;      // 269Sg
			case 3233: return 270.1304360;      // 270Sg
			case 3234: return 271.1339363;      // 271Sg
			case 3235: return 272.1358983;      // 272Sg
			case 3236: return 273.1395854;      // 273Sg
			case 3237: return 260.1216626;      // 260Bh
			case 3238: return 261.1214522;      // 261Bh
			case 3239: return 262.1229733;      // 262Bh
			case 3240: return 263.1229233;      // 263Bh
			case 3241: return 264.1245919;      // 264Bh
			case 3242: return 265.1249125;      // 265Bh
			case 3243: return 266.1267918;      // 266Bh
			case 3244: return 267.1275028;      // 267Bh
			case 3245: return 268.1296941;      // 268Bh
			case 3246: return 269.1304240;      // 269Bh
			case 3247: return 270.1333631;      // 270Bh
			case 3248: return 271.1352648;      // 271Bh
			case 3249: return 272.1382658;      // 272Bh
			case 3250: return 273.1402480;      // 273Bh
			case 3251: return 274.1435565;      // 274Bh
			case 3252: return 275.1456764;      // 275Bh
			case 3253: return 263.1285214;      // 263Hs
			case 3254: return 264.12835731;     // 264Hs
			case 3255: return 265.12979326;     // 265Hs
			case 3256: return 266.13004642;     // 266Hs
			case 3257: return 267.1316710;      // 267Hs
			case 3258: return 268.1318630;      // 268Hs
			case 3259: return 269.1337513;      // 269Hs
			case 3260: return 270.1342927;      // 270Hs
			case 3261: return 271.1371732;      // 271Hs
			case 3262: return 272.1385055;      // 272Hs
			case 3263: return 273.1416840;      // 273Hs
			case 3264: return 274.1433063;      // 274Hs
			case 3265: return 275.1466763;      // 275Hs
			case 3266: return 276.1484686;      // 276Hs
			case 3267: return 277.1519058;      // 277Hs
			case 3268: return 265.1360048;      // 265Mt
			case 3269: return 266.1373733;      // 266Mt
			case 3270: return 267.1371954;      // 267Mt
			case 3271: return 268.1386525;      // 268Mt
			case 3272: return 269.1388250;      // 269Mt
			case 3273: return 270.1403318;      // 270Mt
			case 3274: return 271.1407435;      // 271Mt
			case 3275: return 272.1434152;      // 272Mt
			case 3276: return 273.1444052;      // 273Mt
			case 3277: return 274.1472438;      // 274Mt
			case 3278: return 275.1488250;      // 275Mt
			case 3279: return 276.1515959;      // 276Mt
			case 3280: return 277.1532782;      // 277Mt
			case 3281: return 278.1563168;      // 278Mt
			case 3282: return 279.1580872;      // 279Mt
			case 3283: return 267.1437715;      // 267Ds
			case 3284: return 268.1434832;      // 268Ds
			case 3285: return 269.14475234;     // 269Ds
			case 3286: return 270.14458452;     // 270Ds
			case 3287: return 271.1459510;      // 271Ds
			case 3288: return 272.1460244;      // 272Ds
			case 3289: return 273.1485614;      // 273Ds
			case 3290: return 274.1494142;      // 274Ds
			case 3291: return 275.1520345;      // 275Ds
			case 3292: return 276.1530359;      // 276Ds
			case 3293: return 277.1559141;      // 277Ds
			case 3294: return 278.1570467;      // 278Ds
			case 3295: return 279.1601064;      // 279Ds
			case 3296: return 280.1613189;      // 280Ds
			case 3297: return 281.1645159;      // 281Ds
			case 3298: return 272.1532725;      // 272Rg
			case 3299: return 273.1531356;      // 273Rg
			case 3300: return 274.1552519;      // 274Rg
			case 3301: return 275.1559456;      // 275Rg
			case 3302: return 276.1583368;      // 276Rg
			case 3303: return 277.1590761;      // 277Rg
			case 3304: return 278.1614938;      // 278Rg
			case 3305: return 279.1627251;      // 279Rg
			case 3306: return 280.1651461;      // 280Rg
			case 3307: return 281.1663689;      // 281Rg
			case 3308: return 282.1691272;      // 282Rg
			case 3309: return 283.1705479;      // 283Rg
			case 3310: return 276.1614164;      // 276Cn
			case 3311: return 277.1636415;      // 277Cn
			case 3312: return 278.1641647;      // 278Cn
			case 3313: return 279.1665450;      // 279Cn
			case 3314: return 280.1671563;      // 280Cn
			case 3315: return 281.1697542;      // 281Cn
			case 3316: return 282.1705070;      // 282Cn
			case 3317: return 283.1732765;      // 283Cn
			case 3318: return 284.1741691;      // 284Cn
			case 3319: return 285.1771260;      // 285Cn
			case 3320: return 278.1705820;      // 278Nh
			case 3321: return 279.1709575;      // 279Nh
			case 3322: return 280.1729375;      // 280Nh
			case 3323: return 281.1734875;      // 281Nh
			case 3324: return 282.1756739;      // 282Nh
			case 3325: return 283.1765752;      // 283Nh
			case 3326: return 284.1787362;      // 284Nh
			case 3327: return 285.1797389;      // 285Nh
			case 3328: return 286.1822172;      // 286Nh
			case 3329: return 287.1833981;      // 287Nh
			case 3330: return 285.1836447;      // 285Fl
			case 3331: return 286.1842371;      // 286Fl
			case 3332: return 287.1867866;      // 287Fl
			case 3333: return 288.1875791;      // 288Fl
			case 3334: return 289.1904260;      // 289Fl
			case 3335: return 287.1907052;      // 287Mc
			case 3336: return 288.1927462;      // 288Mc
			case 3337: return 289.1936389;      // 289Mc
			case 3338: return 290.1959873;      // 290Mc
			case 3339: return 291.1970788;      // 291Uup
			case 3340: return 289.1981657;      // 289Lv
			case 3341: return 290.1986471;      // 290Lv
			case 3342: return 291.2010866;      // 291Lv
			case 3343: return 292.2017491;      // 292Lv
			case 3344: return 293.2044960;      // 293Lv
			case 3345: return 291.2055368;      // 291Ts
			case 3346: return 292.2074675;      // 292Ts
			case 3347: return 293.2082489;      // 293Ts
			case 3348: return 294.2104674;      // 294Uus
			case 3349: return 293.2135678;      // 293Og
			case 3350: return 294.2139271;      // 294Og
			case 3351: return 295.2162469;      // 295Og
			  default: return 0.0;
		}
	}

	static inline f64 atomic_mass(c_str symbol)
	{
		auto as_enum = nist::isotope_enum(symbol);
		return nist::atomic_mass(as_enum);
	}

	static constexpr u32 atomic_number(const nist::Isotope a)
	{
		switch (as_u16(a)) {
			case    0: return 1;    // 1H
			case    1: return 1;    // 2H
			case    2: return 1;    // 3H
			case    3: return 1;    // 4H
			case    4: return 1;    // 5H
			case    5: return 1;    // 6H
			case    6: return 1;    // 7H
			case    7: return 2;    // 3He
			case    8: return 2;    // 4He
			case    9: return 2;    // 5He
			case   10: return 2;    // 6He
			case   11: return 2;    // 7He
			case   12: return 2;    // 8He
			case   13: return 2;    // 9He
			case   14: return 2;    // 10He
			case   15: return 3;    // 3Li
			case   16: return 3;    // 4Li
			case   17: return 3;    // 5Li
			case   18: return 3;    // 6Li
			case   19: return 3;    // 7Li
			case   20: return 3;    // 8Li
			case   21: return 3;    // 9Li
			case   22: return 3;    // 10Li
			case   23: return 3;    // 11Li
			case   24: return 3;    // 12Li
			case   25: return 3;    // 13Li
			case   26: return 4;    // 5Be
			case   27: return 4;    // 6Be
			case   28: return 4;    // 7Be
			case   29: return 4;    // 8Be
			case   30: return 4;    // 9Be
			case   31: return 4;    // 10Be
			case   32: return 4;    // 11Be
			case   33: return 4;    // 12Be
			case   34: return 4;    // 13Be
			case   35: return 4;    // 14Be
			case   36: return 4;    // 15Be
			case   37: return 4;    // 16Be
			case   38: return 5;    // 6B
			case   39: return 5;    // 7B
			case   40: return 5;    // 8B
			case   41: return 5;    // 9B
			case   42: return 5;    // 10B
			case   43: return 5;    // 11B
			case   44: return 5;    // 12B
			case   45: return 5;    // 13B
			case   46: return 5;    // 14B
			case   47: return 5;    // 15B
			case   48: return 5;    // 16B
			case   49: return 5;    // 17B
			case   50: return 5;    // 18B
			case   51: return 5;    // 19B
			case   52: return 5;    // 20B
			case   53: return 5;    // 21B
			case   54: return 6;    // 8C
			case   55: return 6;    // 9C
			case   56: return 6;    // 10C
			case   57: return 6;    // 11C
			case   58: return 6;    // 12C
			case   59: return 6;    // 13C
			case   60: return 6;    // 14C
			case   61: return 6;    // 15C
			case   62: return 6;    // 16C
			case   63: return 6;    // 17C
			case   64: return 6;    // 18C
			case   65: return 6;    // 19C
			case   66: return 6;    // 20C
			case   67: return 6;    // 21C
			case   68: return 6;    // 22C
			case   69: return 6;    // 23C
			case   70: return 7;    // 10N
			case   71: return 7;    // 11N
			case   72: return 7;    // 12N
			case   73: return 7;    // 13N
			case   74: return 7;    // 14N
			case   75: return 7;    // 15N
			case   76: return 7;    // 16N
			case   77: return 7;    // 17N
			case   78: return 7;    // 18N
			case   79: return 7;    // 19N
			case   80: return 7;    // 20N
			case   81: return 7;    // 21N
			case   82: return 7;    // 22N
			case   83: return 7;    // 23N
			case   84: return 7;    // 24N
			case   85: return 7;    // 25N
			case   86: return 8;    // 12O
			case   87: return 8;    // 13O
			case   88: return 8;    // 14O
			case   89: return 8;    // 15O
			case   90: return 8;    // 16O
			case   91: return 8;    // 17O
			case   92: return 8;    // 18O
			case   93: return 8;    // 19O
			case   94: return 8;    // 20O
			case   95: return 8;    // 21O
			case   96: return 8;    // 22O
			case   97: return 8;    // 23O
			case   98: return 8;    // 24O
			case   99: return 8;    // 25O
			case  100: return 8;    // 26O
			case  101: return 8;    // 27O
			case  102: return 8;    // 28O
			case  103: return 9;    // 14F
			case  104: return 9;    // 15F
			case  105: return 9;    // 16F
			case  106: return 9;    // 17F
			case  107: return 9;    // 18F
			case  108: return 9;    // 19F
			case  109: return 9;    // 20F
			case  110: return 9;    // 21F
			case  111: return 9;    // 22F
			case  112: return 9;    // 23F
			case  113: return 9;    // 24F
			case  114: return 9;    // 25F
			case  115: return 9;    // 26F
			case  116: return 9;    // 27F
			case  117: return 9;    // 28F
			case  118: return 9;    // 29F
			case  119: return 9;    // 30F
			case  120: return 9;    // 31F
			case  121: return 10;   // 16Ne
			case  122: return 10;   // 17Ne
			case  123: return 10;   // 18Ne
			case  124: return 10;   // 19Ne
			case  125: return 10;   // 20Ne
			case  126: return 10;   // 21Ne
			case  127: return 10;   // 22Ne
			case  128: return 10;   // 23Ne
			case  129: return 10;   // 24Ne
			case  130: return 10;   // 25Ne
			case  131: return 10;   // 26Ne
			case  132: return 10;   // 27Ne
			case  133: return 10;   // 28Ne
			case  134: return 10;   // 29Ne
			case  135: return 10;   // 30Ne
			case  136: return 10;   // 31Ne
			case  137: return 10;   // 32Ne
			case  138: return 10;   // 33Ne
			case  139: return 10;   // 34Ne
			case  140: return 11;   // 18Na
			case  141: return 11;   // 19Na
			case  142: return 11;   // 20Na
			case  143: return 11;   // 21Na
			case  144: return 11;   // 22Na
			case  145: return 11;   // 23Na
			case  146: return 11;   // 24Na
			case  147: return 11;   // 25Na
			case  148: return 11;   // 26Na
			case  149: return 11;   // 27Na
			case  150: return 11;   // 28Na
			case  151: return 11;   // 29Na
			case  152: return 11;   // 30Na
			case  153: return 11;   // 31Na
			case  154: return 11;   // 32Na
			case  155: return 11;   // 33Na
			case  156: return 11;   // 34Na
			case  157: return 11;   // 35Na
			case  158: return 11;   // 36Na
			case  159: return 11;   // 37Na
			case  160: return 12;   // 19Mg
			case  161: return 12;   // 20Mg
			case  162: return 12;   // 21Mg
			case  163: return 12;   // 22Mg
			case  164: return 12;   // 23Mg
			case  165: return 12;   // 24Mg
			case  166: return 12;   // 25Mg
			case  167: return 12;   // 26Mg
			case  168: return 12;   // 27Mg
			case  169: return 12;   // 28Mg
			case  170: return 12;   // 29Mg
			case  171: return 12;   // 30Mg
			case  172: return 12;   // 31Mg
			case  173: return 12;   // 32Mg
			case  174: return 12;   // 33Mg
			case  175: return 12;   // 34Mg
			case  176: return 12;   // 35Mg
			case  177: return 12;   // 36Mg
			case  178: return 12;   // 37Mg
			case  179: return 12;   // 38Mg
			case  180: return 12;   // 39Mg
			case  181: return 12;   // 40Mg
			case  182: return 13;   // 21Al
			case  183: return 13;   // 22Al
			case  184: return 13;   // 23Al
			case  185: return 13;   // 24Al
			case  186: return 13;   // 25Al
			case  187: return 13;   // 26Al
			case  188: return 13;   // 27Al
			case  189: return 13;   // 28Al
			case  190: return 13;   // 29Al
			case  191: return 13;   // 30Al
			case  192: return 13;   // 31Al
			case  193: return 13;   // 32Al
			case  194: return 13;   // 33Al
			case  195: return 13;   // 34Al
			case  196: return 13;   // 35Al
			case  197: return 13;   // 36Al
			case  198: return 13;   // 37Al
			case  199: return 13;   // 38Al
			case  200: return 13;   // 39Al
			case  201: return 13;   // 40Al
			case  202: return 13;   // 41Al
			case  203: return 13;   // 42Al
			case  204: return 13;   // 43Al
			case  205: return 14;   // 22Si
			case  206: return 14;   // 23Si
			case  207: return 14;   // 24Si
			case  208: return 14;   // 25Si
			case  209: return 14;   // 26Si
			case  210: return 14;   // 27Si
			case  211: return 14;   // 28Si
			case  212: return 14;   // 29Si
			case  213: return 14;   // 30Si
			case  214: return 14;   // 31Si
			case  215: return 14;   // 32Si
			case  216: return 14;   // 33Si
			case  217: return 14;   // 34Si
			case  218: return 14;   // 35Si
			case  219: return 14;   // 36Si
			case  220: return 14;   // 37Si
			case  221: return 14;   // 38Si
			case  222: return 14;   // 39Si
			case  223: return 14;   // 40Si
			case  224: return 14;   // 41Si
			case  225: return 14;   // 42Si
			case  226: return 14;   // 43Si
			case  227: return 14;   // 44Si
			case  228: return 14;   // 45Si
			case  229: return 15;   // 24P
			case  230: return 15;   // 25P
			case  231: return 15;   // 26P
			case  232: return 15;   // 27P
			case  233: return 15;   // 28P
			case  234: return 15;   // 29P
			case  235: return 15;   // 30P
			case  236: return 15;   // 31P
			case  237: return 15;   // 32P
			case  238: return 15;   // 33P
			case  239: return 15;   // 34P
			case  240: return 15;   // 35P
			case  241: return 15;   // 36P
			case  242: return 15;   // 37P
			case  243: return 15;   // 38P
			case  244: return 15;   // 39P
			case  245: return 15;   // 40P
			case  246: return 15;   // 41P
			case  247: return 15;   // 42P
			case  248: return 15;   // 43P
			case  249: return 15;   // 44P
			case  250: return 15;   // 45P
			case  251: return 15;   // 46P
			case  252: return 15;   // 47P
			case  253: return 16;   // 26S
			case  254: return 16;   // 27S
			case  255: return 16;   // 28S
			case  256: return 16;   // 29S
			case  257: return 16;   // 30S
			case  258: return 16;   // 31S
			case  259: return 16;   // 32S
			case  260: return 16;   // 33S
			case  261: return 16;   // 34S
			case  262: return 16;   // 35S
			case  263: return 16;   // 36S
			case  264: return 16;   // 37S
			case  265: return 16;   // 38S
			case  266: return 16;   // 39S
			case  267: return 16;   // 40S
			case  268: return 16;   // 41S
			case  269: return 16;   // 42S
			case  270: return 16;   // 43S
			case  271: return 16;   // 44S
			case  272: return 16;   // 45S
			case  273: return 16;   // 46S
			case  274: return 16;   // 47S
			case  275: return 16;   // 48S
			case  276: return 16;   // 49S
			case  277: return 17;   // 28Cl
			case  278: return 17;   // 29Cl
			case  279: return 17;   // 30Cl
			case  280: return 17;   // 31Cl
			case  281: return 17;   // 32Cl
			case  282: return 17;   // 33Cl
			case  283: return 17;   // 34Cl
			case  284: return 17;   // 35Cl
			case  285: return 17;   // 36Cl
			case  286: return 17;   // 37Cl
			case  287: return 17;   // 38Cl
			case  288: return 17;   // 39Cl
			case  289: return 17;   // 40Cl
			case  290: return 17;   // 41Cl
			case  291: return 17;   // 42Cl
			case  292: return 17;   // 43Cl
			case  293: return 17;   // 44Cl
			case  294: return 17;   // 45Cl
			case  295: return 17;   // 46Cl
			case  296: return 17;   // 47Cl
			case  297: return 17;   // 48Cl
			case  298: return 17;   // 49Cl
			case  299: return 17;   // 50Cl
			case  300: return 17;   // 51Cl
			case  301: return 18;   // 30Ar
			case  302: return 18;   // 31Ar
			case  303: return 18;   // 32Ar
			case  304: return 18;   // 33Ar
			case  305: return 18;   // 34Ar
			case  306: return 18;   // 35Ar
			case  307: return 18;   // 36Ar
			case  308: return 18;   // 37Ar
			case  309: return 18;   // 38Ar
			case  310: return 18;   // 39Ar
			case  311: return 18;   // 40Ar
			case  312: return 18;   // 41Ar
			case  313: return 18;   // 42Ar
			case  314: return 18;   // 43Ar
			case  315: return 18;   // 44Ar
			case  316: return 18;   // 45Ar
			case  317: return 18;   // 46Ar
			case  318: return 18;   // 47Ar
			case  319: return 18;   // 48Ar
			case  320: return 18;   // 49Ar
			case  321: return 18;   // 50Ar
			case  322: return 18;   // 51Ar
			case  323: return 18;   // 52Ar
			case  324: return 18;   // 53Ar
			case  325: return 19;   // 32K
			case  326: return 19;   // 33K
			case  327: return 19;   // 34K
			case  328: return 19;   // 35K
			case  329: return 19;   // 36K
			case  330: return 19;   // 37K
			case  331: return 19;   // 38K
			case  332: return 19;   // 39K
			case  333: return 19;   // 40K
			case  334: return 19;   // 41K
			case  335: return 19;   // 42K
			case  336: return 19;   // 43K
			case  337: return 19;   // 44K
			case  338: return 19;   // 45K
			case  339: return 19;   // 46K
			case  340: return 19;   // 47K
			case  341: return 19;   // 48K
			case  342: return 19;   // 49K
			case  343: return 19;   // 50K
			case  344: return 19;   // 51K
			case  345: return 19;   // 52K
			case  346: return 19;   // 53K
			case  347: return 19;   // 54K
			case  348: return 19;   // 55K
			case  349: return 19;   // 56K
			case  350: return 20;   // 34Ca
			case  351: return 20;   // 35Ca
			case  352: return 20;   // 36Ca
			case  353: return 20;   // 37Ca
			case  354: return 20;   // 38Ca
			case  355: return 20;   // 39Ca
			case  356: return 20;   // 40Ca
			case  357: return 20;   // 41Ca
			case  358: return 20;   // 42Ca
			case  359: return 20;   // 43Ca
			case  360: return 20;   // 44Ca
			case  361: return 20;   // 45Ca
			case  362: return 20;   // 46Ca
			case  363: return 20;   // 47Ca
			case  364: return 20;   // 48Ca
			case  365: return 20;   // 49Ca
			case  366: return 20;   // 50Ca
			case  367: return 20;   // 51Ca
			case  368: return 20;   // 52Ca
			case  369: return 20;   // 53Ca
			case  370: return 20;   // 54Ca
			case  371: return 20;   // 55Ca
			case  372: return 20;   // 56Ca
			case  373: return 20;   // 57Ca
			case  374: return 20;   // 58Ca
			case  375: return 21;   // 36Sc
			case  376: return 21;   // 37Sc
			case  377: return 21;   // 38Sc
			case  378: return 21;   // 39Sc
			case  379: return 21;   // 40Sc
			case  380: return 21;   // 41Sc
			case  381: return 21;   // 42Sc
			case  382: return 21;   // 43Sc
			case  383: return 21;   // 44Sc
			case  384: return 21;   // 45Sc
			case  385: return 21;   // 46Sc
			case  386: return 21;   // 47Sc
			case  387: return 21;   // 48Sc
			case  388: return 21;   // 49Sc
			case  389: return 21;   // 50Sc
			case  390: return 21;   // 51Sc
			case  391: return 21;   // 52Sc
			case  392: return 21;   // 53Sc
			case  393: return 21;   // 54Sc
			case  394: return 21;   // 55Sc
			case  395: return 21;   // 56Sc
			case  396: return 21;   // 57Sc
			case  397: return 21;   // 58Sc
			case  398: return 21;   // 59Sc
			case  399: return 21;   // 60Sc
			case  400: return 21;   // 61Sc
			case  401: return 22;   // 38Ti
			case  402: return 22;   // 39Ti
			case  403: return 22;   // 40Ti
			case  404: return 22;   // 41Ti
			case  405: return 22;   // 42Ti
			case  406: return 22;   // 43Ti
			case  407: return 22;   // 44Ti
			case  408: return 22;   // 45Ti
			case  409: return 22;   // 46Ti
			case  410: return 22;   // 47Ti
			case  411: return 22;   // 48Ti
			case  412: return 22;   // 49Ti
			case  413: return 22;   // 50Ti
			case  414: return 22;   // 51Ti
			case  415: return 22;   // 52Ti
			case  416: return 22;   // 53Ti
			case  417: return 22;   // 54Ti
			case  418: return 22;   // 55Ti
			case  419: return 22;   // 56Ti
			case  420: return 22;   // 57Ti
			case  421: return 22;   // 58Ti
			case  422: return 22;   // 59Ti
			case  423: return 22;   // 60Ti
			case  424: return 22;   // 61Ti
			case  425: return 22;   // 62Ti
			case  426: return 22;   // 63Ti
			case  427: return 23;   // 40V
			case  428: return 23;   // 41V
			case  429: return 23;   // 42V
			case  430: return 23;   // 43V
			case  431: return 23;   // 44V
			case  432: return 23;   // 45V
			case  433: return 23;   // 46V
			case  434: return 23;   // 47V
			case  435: return 23;   // 48V
			case  436: return 23;   // 49V
			case  437: return 23;   // 50V
			case  438: return 23;   // 51V
			case  439: return 23;   // 52V
			case  440: return 23;   // 53V
			case  441: return 23;   // 54V
			case  442: return 23;   // 55V
			case  443: return 23;   // 56V
			case  444: return 23;   // 57V
			case  445: return 23;   // 58V
			case  446: return 23;   // 59V
			case  447: return 23;   // 60V
			case  448: return 23;   // 61V
			case  449: return 23;   // 62V
			case  450: return 23;   // 63V
			case  451: return 23;   // 64V
			case  452: return 23;   // 65V
			case  453: return 23;   // 66V
			case  454: return 24;   // 42Cr
			case  455: return 24;   // 43Cr
			case  456: return 24;   // 44Cr
			case  457: return 24;   // 45Cr
			case  458: return 24;   // 46Cr
			case  459: return 24;   // 47Cr
			case  460: return 24;   // 48Cr
			case  461: return 24;   // 49Cr
			case  462: return 24;   // 50Cr
			case  463: return 24;   // 51Cr
			case  464: return 24;   // 52Cr
			case  465: return 24;   // 53Cr
			case  466: return 24;   // 54Cr
			case  467: return 24;   // 55Cr
			case  468: return 24;   // 56Cr
			case  469: return 24;   // 57Cr
			case  470: return 24;   // 58Cr
			case  471: return 24;   // 59Cr
			case  472: return 24;   // 60Cr
			case  473: return 24;   // 61Cr
			case  474: return 24;   // 62Cr
			case  475: return 24;   // 63Cr
			case  476: return 24;   // 64Cr
			case  477: return 24;   // 65Cr
			case  478: return 24;   // 66Cr
			case  479: return 24;   // 67Cr
			case  480: return 24;   // 68Cr
			case  481: return 25;   // 44Mn
			case  482: return 25;   // 45Mn
			case  483: return 25;   // 46Mn
			case  484: return 25;   // 47Mn
			case  485: return 25;   // 48Mn
			case  486: return 25;   // 49Mn
			case  487: return 25;   // 50Mn
			case  488: return 25;   // 51Mn
			case  489: return 25;   // 52Mn
			case  490: return 25;   // 53Mn
			case  491: return 25;   // 54Mn
			case  492: return 25;   // 55Mn
			case  493: return 25;   // 56Mn
			case  494: return 25;   // 57Mn
			case  495: return 25;   // 58Mn
			case  496: return 25;   // 59Mn
			case  497: return 25;   // 60Mn
			case  498: return 25;   // 61Mn
			case  499: return 25;   // 62Mn
			case  500: return 25;   // 63Mn
			case  501: return 25;   // 64Mn
			case  502: return 25;   // 65Mn
			case  503: return 25;   // 66Mn
			case  504: return 25;   // 67Mn
			case  505: return 25;   // 68Mn
			case  506: return 25;   // 69Mn
			case  507: return 25;   // 70Mn
			case  508: return 25;   // 71Mn
			case  509: return 26;   // 45Fe
			case  510: return 26;   // 46Fe
			case  511: return 26;   // 47Fe
			case  512: return 26;   // 48Fe
			case  513: return 26;   // 49Fe
			case  514: return 26;   // 50Fe
			case  515: return 26;   // 51Fe
			case  516: return 26;   // 52Fe
			case  517: return 26;   // 53Fe
			case  518: return 26;   // 54Fe
			case  519: return 26;   // 55Fe
			case  520: return 26;   // 56Fe
			case  521: return 26;   // 57Fe
			case  522: return 26;   // 58Fe
			case  523: return 26;   // 59Fe
			case  524: return 26;   // 60Fe
			case  525: return 26;   // 61Fe
			case  526: return 26;   // 62Fe
			case  527: return 26;   // 63Fe
			case  528: return 26;   // 64Fe
			case  529: return 26;   // 65Fe
			case  530: return 26;   // 66Fe
			case  531: return 26;   // 67Fe
			case  532: return 26;   // 68Fe
			case  533: return 26;   // 69Fe
			case  534: return 26;   // 70Fe
			case  535: return 26;   // 71Fe
			case  536: return 26;   // 72Fe
			case  537: return 26;   // 73Fe
			case  538: return 26;   // 74Fe
			case  539: return 27;   // 47Co
			case  540: return 27;   // 48Co
			case  541: return 27;   // 49Co
			case  542: return 27;   // 50Co
			case  543: return 27;   // 51Co
			case  544: return 27;   // 52Co
			case  545: return 27;   // 53Co
			case  546: return 27;   // 54Co
			case  547: return 27;   // 55Co
			case  548: return 27;   // 56Co
			case  549: return 27;   // 57Co
			case  550: return 27;   // 58Co
			case  551: return 27;   // 59Co
			case  552: return 27;   // 60Co
			case  553: return 27;   // 61Co
			case  554: return 27;   // 62Co
			case  555: return 27;   // 63Co
			case  556: return 27;   // 64Co
			case  557: return 27;   // 65Co
			case  558: return 27;   // 66Co
			case  559: return 27;   // 67Co
			case  560: return 27;   // 68Co
			case  561: return 27;   // 69Co
			case  562: return 27;   // 70Co
			case  563: return 27;   // 71Co
			case  564: return 27;   // 72Co
			case  565: return 27;   // 73Co
			case  566: return 27;   // 74Co
			case  567: return 27;   // 75Co
			case  568: return 27;   // 76Co
			case  569: return 28;   // 48Ni
			case  570: return 28;   // 49Ni
			case  571: return 28;   // 50Ni
			case  572: return 28;   // 51Ni
			case  573: return 28;   // 52Ni
			case  574: return 28;   // 53Ni
			case  575: return 28;   // 54Ni
			case  576: return 28;   // 55Ni
			case  577: return 28;   // 56Ni
			case  578: return 28;   // 57Ni
			case  579: return 28;   // 58Ni
			case  580: return 28;   // 59Ni
			case  581: return 28;   // 60Ni
			case  582: return 28;   // 61Ni
			case  583: return 28;   // 62Ni
			case  584: return 28;   // 63Ni
			case  585: return 28;   // 64Ni
			case  586: return 28;   // 65Ni
			case  587: return 28;   // 66Ni
			case  588: return 28;   // 67Ni
			case  589: return 28;   // 68Ni
			case  590: return 28;   // 69Ni
			case  591: return 28;   // 70Ni
			case  592: return 28;   // 71Ni
			case  593: return 28;   // 72Ni
			case  594: return 28;   // 73Ni
			case  595: return 28;   // 74Ni
			case  596: return 28;   // 75Ni
			case  597: return 28;   // 76Ni
			case  598: return 28;   // 77Ni
			case  599: return 28;   // 78Ni
			case  600: return 28;   // 79Ni
			case  601: return 29;   // 52Cu
			case  602: return 29;   // 53Cu
			case  603: return 29;   // 54Cu
			case  604: return 29;   // 55Cu
			case  605: return 29;   // 56Cu
			case  606: return 29;   // 57Cu
			case  607: return 29;   // 58Cu
			case  608: return 29;   // 59Cu
			case  609: return 29;   // 60Cu
			case  610: return 29;   // 61Cu
			case  611: return 29;   // 62Cu
			case  612: return 29;   // 63Cu
			case  613: return 29;   // 64Cu
			case  614: return 29;   // 65Cu
			case  615: return 29;   // 66Cu
			case  616: return 29;   // 67Cu
			case  617: return 29;   // 68Cu
			case  618: return 29;   // 69Cu
			case  619: return 29;   // 70Cu
			case  620: return 29;   // 71Cu
			case  621: return 29;   // 72Cu
			case  622: return 29;   // 73Cu
			case  623: return 29;   // 74Cu
			case  624: return 29;   // 75Cu
			case  625: return 29;   // 76Cu
			case  626: return 29;   // 77Cu
			case  627: return 29;   // 78Cu
			case  628: return 29;   // 79Cu
			case  629: return 29;   // 80Cu
			case  630: return 29;   // 81Cu
			case  631: return 29;   // 82Cu
			case  632: return 30;   // 54Zn
			case  633: return 30;   // 55Zn
			case  634: return 30;   // 56Zn
			case  635: return 30;   // 57Zn
			case  636: return 30;   // 58Zn
			case  637: return 30;   // 59Zn
			case  638: return 30;   // 60Zn
			case  639: return 30;   // 61Zn
			case  640: return 30;   // 62Zn
			case  641: return 30;   // 63Zn
			case  642: return 30;   // 64Zn
			case  643: return 30;   // 65Zn
			case  644: return 30;   // 66Zn
			case  645: return 30;   // 67Zn
			case  646: return 30;   // 68Zn
			case  647: return 30;   // 69Zn
			case  648: return 30;   // 70Zn
			case  649: return 30;   // 71Zn
			case  650: return 30;   // 72Zn
			case  651: return 30;   // 73Zn
			case  652: return 30;   // 74Zn
			case  653: return 30;   // 75Zn
			case  654: return 30;   // 76Zn
			case  655: return 30;   // 77Zn
			case  656: return 30;   // 78Zn
			case  657: return 30;   // 79Zn
			case  658: return 30;   // 80Zn
			case  659: return 30;   // 81Zn
			case  660: return 30;   // 82Zn
			case  661: return 30;   // 83Zn
			case  662: return 30;   // 84Zn
			case  663: return 30;   // 85Zn
			case  664: return 31;   // 56Ga
			case  665: return 31;   // 57Ga
			case  666: return 31;   // 58Ga
			case  667: return 31;   // 59Ga
			case  668: return 31;   // 60Ga
			case  669: return 31;   // 61Ga
			case  670: return 31;   // 62Ga
			case  671: return 31;   // 63Ga
			case  672: return 31;   // 64Ga
			case  673: return 31;   // 65Ga
			case  674: return 31;   // 66Ga
			case  675: return 31;   // 67Ga
			case  676: return 31;   // 68Ga
			case  677: return 31;   // 69Ga
			case  678: return 31;   // 70Ga
			case  679: return 31;   // 71Ga
			case  680: return 31;   // 72Ga
			case  681: return 31;   // 73Ga
			case  682: return 31;   // 74Ga
			case  683: return 31;   // 75Ga
			case  684: return 31;   // 76Ga
			case  685: return 31;   // 77Ga
			case  686: return 31;   // 78Ga
			case  687: return 31;   // 79Ga
			case  688: return 31;   // 80Ga
			case  689: return 31;   // 81Ga
			case  690: return 31;   // 82Ga
			case  691: return 31;   // 83Ga
			case  692: return 31;   // 84Ga
			case  693: return 31;   // 85Ga
			case  694: return 31;   // 86Ga
			case  695: return 31;   // 87Ga
			case  696: return 32;   // 58Ge
			case  697: return 32;   // 59Ge
			case  698: return 32;   // 60Ge
			case  699: return 32;   // 61Ge
			case  700: return 32;   // 62Ge
			case  701: return 32;   // 63Ge
			case  702: return 32;   // 64Ge
			case  703: return 32;   // 65Ge
			case  704: return 32;   // 66Ge
			case  705: return 32;   // 67Ge
			case  706: return 32;   // 68Ge
			case  707: return 32;   // 69Ge
			case  708: return 32;   // 70Ge
			case  709: return 32;   // 71Ge
			case  710: return 32;   // 72Ge
			case  711: return 32;   // 73Ge
			case  712: return 32;   // 74Ge
			case  713: return 32;   // 75Ge
			case  714: return 32;   // 76Ge
			case  715: return 32;   // 77Ge
			case  716: return 32;   // 78Ge
			case  717: return 32;   // 79Ge
			case  718: return 32;   // 80Ge
			case  719: return 32;   // 81Ge
			case  720: return 32;   // 82Ge
			case  721: return 32;   // 83Ge
			case  722: return 32;   // 84Ge
			case  723: return 32;   // 85Ge
			case  724: return 32;   // 86Ge
			case  725: return 32;   // 87Ge
			case  726: return 32;   // 88Ge
			case  727: return 32;   // 89Ge
			case  728: return 32;   // 90Ge
			case  729: return 33;   // 60As
			case  730: return 33;   // 61As
			case  731: return 33;   // 62As
			case  732: return 33;   // 63As
			case  733: return 33;   // 64As
			case  734: return 33;   // 65As
			case  735: return 33;   // 66As
			case  736: return 33;   // 67As
			case  737: return 33;   // 68As
			case  738: return 33;   // 69As
			case  739: return 33;   // 70As
			case  740: return 33;   // 71As
			case  741: return 33;   // 72As
			case  742: return 33;   // 73As
			case  743: return 33;   // 74As
			case  744: return 33;   // 75As
			case  745: return 33;   // 76As
			case  746: return 33;   // 77As
			case  747: return 33;   // 78As
			case  748: return 33;   // 79As
			case  749: return 33;   // 80As
			case  750: return 33;   // 81As
			case  751: return 33;   // 82As
			case  752: return 33;   // 83As
			case  753: return 33;   // 84As
			case  754: return 33;   // 85As
			case  755: return 33;   // 86As
			case  756: return 33;   // 87As
			case  757: return 33;   // 88As
			case  758: return 33;   // 89As
			case  759: return 33;   // 90As
			case  760: return 33;   // 91As
			case  761: return 33;   // 92As
			case  762: return 34;   // 64Se
			case  763: return 34;   // 65Se
			case  764: return 34;   // 66Se
			case  765: return 34;   // 67Se
			case  766: return 34;   // 68Se
			case  767: return 34;   // 69Se
			case  768: return 34;   // 70Se
			case  769: return 34;   // 71Se
			case  770: return 34;   // 72Se
			case  771: return 34;   // 73Se
			case  772: return 34;   // 74Se
			case  773: return 34;   // 75Se
			case  774: return 34;   // 76Se
			case  775: return 34;   // 77Se
			case  776: return 34;   // 78Se
			case  777: return 34;   // 79Se
			case  778: return 34;   // 80Se
			case  779: return 34;   // 81Se
			case  780: return 34;   // 82Se
			case  781: return 34;   // 83Se
			case  782: return 34;   // 84Se
			case  783: return 34;   // 85Se
			case  784: return 34;   // 86Se
			case  785: return 34;   // 87Se
			case  786: return 34;   // 88Se
			case  787: return 34;   // 89Se
			case  788: return 34;   // 90Se
			case  789: return 34;   // 91Se
			case  790: return 34;   // 92Se
			case  791: return 34;   // 93Se
			case  792: return 34;   // 94Se
			case  793: return 34;   // 95Se
			case  794: return 35;   // 67Br
			case  795: return 35;   // 68Br
			case  796: return 35;   // 69Br
			case  797: return 35;   // 70Br
			case  798: return 35;   // 71Br
			case  799: return 35;   // 72Br
			case  800: return 35;   // 73Br
			case  801: return 35;   // 74Br
			case  802: return 35;   // 75Br
			case  803: return 35;   // 76Br
			case  804: return 35;   // 77Br
			case  805: return 35;   // 78Br
			case  806: return 35;   // 79Br
			case  807: return 35;   // 80Br
			case  808: return 35;   // 81Br
			case  809: return 35;   // 82Br
			case  810: return 35;   // 83Br
			case  811: return 35;   // 84Br
			case  812: return 35;   // 85Br
			case  813: return 35;   // 86Br
			case  814: return 35;   // 87Br
			case  815: return 35;   // 88Br
			case  816: return 35;   // 89Br
			case  817: return 35;   // 90Br
			case  818: return 35;   // 91Br
			case  819: return 35;   // 92Br
			case  820: return 35;   // 93Br
			case  821: return 35;   // 94Br
			case  822: return 35;   // 95Br
			case  823: return 35;   // 96Br
			case  824: return 35;   // 97Br
			case  825: return 35;   // 98Br
			case  826: return 36;   // 69Kr
			case  827: return 36;   // 70Kr
			case  828: return 36;   // 71Kr
			case  829: return 36;   // 72Kr
			case  830: return 36;   // 73Kr
			case  831: return 36;   // 74Kr
			case  832: return 36;   // 75Kr
			case  833: return 36;   // 76Kr
			case  834: return 36;   // 77Kr
			case  835: return 36;   // 78Kr
			case  836: return 36;   // 79Kr
			case  837: return 36;   // 80Kr
			case  838: return 36;   // 81Kr
			case  839: return 36;   // 82Kr
			case  840: return 36;   // 83Kr
			case  841: return 36;   // 84Kr
			case  842: return 36;   // 85Kr
			case  843: return 36;   // 86Kr
			case  844: return 36;   // 87Kr
			case  845: return 36;   // 88Kr
			case  846: return 36;   // 89Kr
			case  847: return 36;   // 90Kr
			case  848: return 36;   // 91Kr
			case  849: return 36;   // 92Kr
			case  850: return 36;   // 93Kr
			case  851: return 36;   // 94Kr
			case  852: return 36;   // 95Kr
			case  853: return 36;   // 96Kr
			case  854: return 36;   // 97Kr
			case  855: return 36;   // 98Kr
			case  856: return 36;   // 99Kr
			case  857: return 36;   // 100Kr
			case  858: return 36;   // 101Kr
			case  859: return 37;   // 71Rb
			case  860: return 37;   // 72Rb
			case  861: return 37;   // 73Rb
			case  862: return 37;   // 74Rb
			case  863: return 37;   // 75Rb
			case  864: return 37;   // 76Rb
			case  865: return 37;   // 77Rb
			case  866: return 37;   // 78Rb
			case  867: return 37;   // 79Rb
			case  868: return 37;   // 80Rb
			case  869: return 37;   // 81Rb
			case  870: return 37;   // 82Rb
			case  871: return 37;   // 83Rb
			case  872: return 37;   // 84Rb
			case  873: return 37;   // 85Rb
			case  874: return 37;   // 86Rb
			case  875: return 37;   // 87Rb
			case  876: return 37;   // 88Rb
			case  877: return 37;   // 89Rb
			case  878: return 37;   // 90Rb
			case  879: return 37;   // 91Rb
			case  880: return 37;   // 92Rb
			case  881: return 37;   // 93Rb
			case  882: return 37;   // 94Rb
			case  883: return 37;   // 95Rb
			case  884: return 37;   // 96Rb
			case  885: return 37;   // 97Rb
			case  886: return 37;   // 98Rb
			case  887: return 37;   // 99Rb
			case  888: return 37;   // 100Rb
			case  889: return 37;   // 101Rb
			case  890: return 37;   // 102Rb
			case  891: return 37;   // 103Rb
			case  892: return 38;   // 73Sr
			case  893: return 38;   // 74Sr
			case  894: return 38;   // 75Sr
			case  895: return 38;   // 76Sr
			case  896: return 38;   // 77Sr
			case  897: return 38;   // 78Sr
			case  898: return 38;   // 79Sr
			case  899: return 38;   // 80Sr
			case  900: return 38;   // 81Sr
			case  901: return 38;   // 82Sr
			case  902: return 38;   // 83Sr
			case  903: return 38;   // 84Sr
			case  904: return 38;   // 85Sr
			case  905: return 38;   // 86Sr
			case  906: return 38;   // 87Sr
			case  907: return 38;   // 88Sr
			case  908: return 38;   // 89Sr
			case  909: return 38;   // 90Sr
			case  910: return 38;   // 91Sr
			case  911: return 38;   // 92Sr
			case  912: return 38;   // 93Sr
			case  913: return 38;   // 94Sr
			case  914: return 38;   // 95Sr
			case  915: return 38;   // 96Sr
			case  916: return 38;   // 97Sr
			case  917: return 38;   // 98Sr
			case  918: return 38;   // 99Sr
			case  919: return 38;   // 100Sr
			case  920: return 38;   // 101Sr
			case  921: return 38;   // 102Sr
			case  922: return 38;   // 103Sr
			case  923: return 38;   // 104Sr
			case  924: return 38;   // 105Sr
			case  925: return 38;   // 106Sr
			case  926: return 38;   // 107Sr
			case  927: return 39;   // 76Y
			case  928: return 39;   // 77Y
			case  929: return 39;   // 78Y
			case  930: return 39;   // 79Y
			case  931: return 39;   // 80Y
			case  932: return 39;   // 81Y
			case  933: return 39;   // 82Y
			case  934: return 39;   // 83Y
			case  935: return 39;   // 84Y
			case  936: return 39;   // 85Y
			case  937: return 39;   // 86Y
			case  938: return 39;   // 87Y
			case  939: return 39;   // 88Y
			case  940: return 39;   // 89Y
			case  941: return 39;   // 90Y
			case  942: return 39;   // 91Y
			case  943: return 39;   // 92Y
			case  944: return 39;   // 93Y
			case  945: return 39;   // 94Y
			case  946: return 39;   // 95Y
			case  947: return 39;   // 96Y
			case  948: return 39;   // 97Y
			case  949: return 39;   // 98Y
			case  950: return 39;   // 99Y
			case  951: return 39;   // 100Y
			case  952: return 39;   // 101Y
			case  953: return 39;   // 102Y
			case  954: return 39;   // 103Y
			case  955: return 39;   // 104Y
			case  956: return 39;   // 105Y
			case  957: return 39;   // 106Y
			case  958: return 39;   // 107Y
			case  959: return 39;   // 108Y
			case  960: return 39;   // 109Y
			case  961: return 40;   // 78Zr
			case  962: return 40;   // 79Zr
			case  963: return 40;   // 80Zr
			case  964: return 40;   // 81Zr
			case  965: return 40;   // 82Zr
			case  966: return 40;   // 83Zr
			case  967: return 40;   // 84Zr
			case  968: return 40;   // 85Zr
			case  969: return 40;   // 86Zr
			case  970: return 40;   // 87Zr
			case  971: return 40;   // 88Zr
			case  972: return 40;   // 89Zr
			case  973: return 40;   // 90Zr
			case  974: return 40;   // 91Zr
			case  975: return 40;   // 92Zr
			case  976: return 40;   // 93Zr
			case  977: return 40;   // 94Zr
			case  978: return 40;   // 95Zr
			case  979: return 40;   // 96Zr
			case  980: return 40;   // 97Zr
			case  981: return 40;   // 98Zr
			case  982: return 40;   // 99Zr
			case  983: return 40;   // 100Zr
			case  984: return 40;   // 101Zr
			case  985: return 40;   // 102Zr
			case  986: return 40;   // 103Zr
			case  987: return 40;   // 104Zr
			case  988: return 40;   // 105Zr
			case  989: return 40;   // 106Zr
			case  990: return 40;   // 107Zr
			case  991: return 40;   // 108Zr
			case  992: return 40;   // 109Zr
			case  993: return 40;   // 110Zr
			case  994: return 40;   // 111Zr
			case  995: return 40;   // 112Zr
			case  996: return 41;   // 81Nb
			case  997: return 41;   // 82Nb
			case  998: return 41;   // 83Nb
			case  999: return 41;   // 84Nb
			case 1000: return 41;   // 85Nb
			case 1001: return 41;   // 86Nb
			case 1002: return 41;   // 87Nb
			case 1003: return 41;   // 88Nb
			case 1004: return 41;   // 89Nb
			case 1005: return 41;   // 90Nb
			case 1006: return 41;   // 91Nb
			case 1007: return 41;   // 92Nb
			case 1008: return 41;   // 93Nb
			case 1009: return 41;   // 94Nb
			case 1010: return 41;   // 95Nb
			case 1011: return 41;   // 96Nb
			case 1012: return 41;   // 97Nb
			case 1013: return 41;   // 98Nb
			case 1014: return 41;   // 99Nb
			case 1015: return 41;   // 100Nb
			case 1016: return 41;   // 101Nb
			case 1017: return 41;   // 102Nb
			case 1018: return 41;   // 103Nb
			case 1019: return 41;   // 104Nb
			case 1020: return 41;   // 105Nb
			case 1021: return 41;   // 106Nb
			case 1022: return 41;   // 107Nb
			case 1023: return 41;   // 108Nb
			case 1024: return 41;   // 109Nb
			case 1025: return 41;   // 110Nb
			case 1026: return 41;   // 111Nb
			case 1027: return 41;   // 112Nb
			case 1028: return 41;   // 113Nb
			case 1029: return 41;   // 114Nb
			case 1030: return 41;   // 115Nb
			case 1031: return 42;   // 83Mo
			case 1032: return 42;   // 84Mo
			case 1033: return 42;   // 85Mo
			case 1034: return 42;   // 86Mo
			case 1035: return 42;   // 87Mo
			case 1036: return 42;   // 88Mo
			case 1037: return 42;   // 89Mo
			case 1038: return 42;   // 90Mo
			case 1039: return 42;   // 91Mo
			case 1040: return 42;   // 92Mo
			case 1041: return 42;   // 93Mo
			case 1042: return 42;   // 94Mo
			case 1043: return 42;   // 95Mo
			case 1044: return 42;   // 96Mo
			case 1045: return 42;   // 97Mo
			case 1046: return 42;   // 98Mo
			case 1047: return 42;   // 99Mo
			case 1048: return 42;   // 100Mo
			case 1049: return 42;   // 101Mo
			case 1050: return 42;   // 102Mo
			case 1051: return 42;   // 103Mo
			case 1052: return 42;   // 104Mo
			case 1053: return 42;   // 105Mo
			case 1054: return 42;   // 106Mo
			case 1055: return 42;   // 107Mo
			case 1056: return 42;   // 108Mo
			case 1057: return 42;   // 109Mo
			case 1058: return 42;   // 110Mo
			case 1059: return 42;   // 111Mo
			case 1060: return 42;   // 112Mo
			case 1061: return 42;   // 113Mo
			case 1062: return 42;   // 114Mo
			case 1063: return 42;   // 115Mo
			case 1064: return 42;   // 116Mo
			case 1065: return 42;   // 117Mo
			case 1066: return 43;   // 85Tc
			case 1067: return 43;   // 86Tc
			case 1068: return 43;   // 87Tc
			case 1069: return 43;   // 88Tc
			case 1070: return 43;   // 89Tc
			case 1071: return 43;   // 90Tc
			case 1072: return 43;   // 91Tc
			case 1073: return 43;   // 92Tc
			case 1074: return 43;   // 93Tc
			case 1075: return 43;   // 94Tc
			case 1076: return 43;   // 95Tc
			case 1077: return 43;   // 96Tc
			case 1078: return 43;   // 97Tc
			case 1079: return 43;   // 98Tc
			case 1080: return 43;   // 99Tc
			case 1081: return 43;   // 100Tc
			case 1082: return 43;   // 101Tc
			case 1083: return 43;   // 102Tc
			case 1084: return 43;   // 103Tc
			case 1085: return 43;   // 104Tc
			case 1086: return 43;   // 105Tc
			case 1087: return 43;   // 106Tc
			case 1088: return 43;   // 107Tc
			case 1089: return 43;   // 108Tc
			case 1090: return 43;   // 109Tc
			case 1091: return 43;   // 110Tc
			case 1092: return 43;   // 111Tc
			case 1093: return 43;   // 112Tc
			case 1094: return 43;   // 113Tc
			case 1095: return 43;   // 114Tc
			case 1096: return 43;   // 115Tc
			case 1097: return 43;   // 116Tc
			case 1098: return 43;   // 117Tc
			case 1099: return 43;   // 118Tc
			case 1100: return 43;   // 119Tc
			case 1101: return 43;   // 120Tc
			case 1102: return 44;   // 87Ru
			case 1103: return 44;   // 88Ru
			case 1104: return 44;   // 89Ru
			case 1105: return 44;   // 90Ru
			case 1106: return 44;   // 91Ru
			case 1107: return 44;   // 92Ru
			case 1108: return 44;   // 93Ru
			case 1109: return 44;   // 94Ru
			case 1110: return 44;   // 95Ru
			case 1111: return 44;   // 96Ru
			case 1112: return 44;   // 97Ru
			case 1113: return 44;   // 98Ru
			case 1114: return 44;   // 99Ru
			case 1115: return 44;   // 100Ru
			case 1116: return 44;   // 101Ru
			case 1117: return 44;   // 102Ru
			case 1118: return 44;   // 103Ru
			case 1119: return 44;   // 104Ru
			case 1120: return 44;   // 105Ru
			case 1121: return 44;   // 106Ru
			case 1122: return 44;   // 107Ru
			case 1123: return 44;   // 108Ru
			case 1124: return 44;   // 109Ru
			case 1125: return 44;   // 110Ru
			case 1126: return 44;   // 111Ru
			case 1127: return 44;   // 112Ru
			case 1128: return 44;   // 113Ru
			case 1129: return 44;   // 114Ru
			case 1130: return 44;   // 115Ru
			case 1131: return 44;   // 116Ru
			case 1132: return 44;   // 117Ru
			case 1133: return 44;   // 118Ru
			case 1134: return 44;   // 119Ru
			case 1135: return 44;   // 120Ru
			case 1136: return 44;   // 121Ru
			case 1137: return 44;   // 122Ru
			case 1138: return 44;   // 123Ru
			case 1139: return 44;   // 124Ru
			case 1140: return 45;   // 89Rh
			case 1141: return 45;   // 90Rh
			case 1142: return 45;   // 91Rh
			case 1143: return 45;   // 92Rh
			case 1144: return 45;   // 93Rh
			case 1145: return 45;   // 94Rh
			case 1146: return 45;   // 95Rh
			case 1147: return 45;   // 96Rh
			case 1148: return 45;   // 97Rh
			case 1149: return 45;   // 98Rh
			case 1150: return 45;   // 99Rh
			case 1151: return 45;   // 100Rh
			case 1152: return 45;   // 101Rh
			case 1153: return 45;   // 102Rh
			case 1154: return 45;   // 103Rh
			case 1155: return 45;   // 104Rh
			case 1156: return 45;   // 105Rh
			case 1157: return 45;   // 106Rh
			case 1158: return 45;   // 107Rh
			case 1159: return 45;   // 108Rh
			case 1160: return 45;   // 109Rh
			case 1161: return 45;   // 110Rh
			case 1162: return 45;   // 111Rh
			case 1163: return 45;   // 112Rh
			case 1164: return 45;   // 113Rh
			case 1165: return 45;   // 114Rh
			case 1166: return 45;   // 115Rh
			case 1167: return 45;   // 116Rh
			case 1168: return 45;   // 117Rh
			case 1169: return 45;   // 118Rh
			case 1170: return 45;   // 119Rh
			case 1171: return 45;   // 120Rh
			case 1172: return 45;   // 121Rh
			case 1173: return 45;   // 122Rh
			case 1174: return 45;   // 123Rh
			case 1175: return 45;   // 124Rh
			case 1176: return 45;   // 125Rh
			case 1177: return 45;   // 126Rh
			case 1178: return 46;   // 91Pd
			case 1179: return 46;   // 92Pd
			case 1180: return 46;   // 93Pd
			case 1181: return 46;   // 94Pd
			case 1182: return 46;   // 95Pd
			case 1183: return 46;   // 96Pd
			case 1184: return 46;   // 97Pd
			case 1185: return 46;   // 98Pd
			case 1186: return 46;   // 99Pd
			case 1187: return 46;   // 100Pd
			case 1188: return 46;   // 101Pd
			case 1189: return 46;   // 102Pd
			case 1190: return 46;   // 103Pd
			case 1191: return 46;   // 104Pd
			case 1192: return 46;   // 105Pd
			case 1193: return 46;   // 106Pd
			case 1194: return 46;   // 107Pd
			case 1195: return 46;   // 108Pd
			case 1196: return 46;   // 109Pd
			case 1197: return 46;   // 110Pd
			case 1198: return 46;   // 111Pd
			case 1199: return 46;   // 112Pd
			case 1200: return 46;   // 113Pd
			case 1201: return 46;   // 114Pd
			case 1202: return 46;   // 115Pd
			case 1203: return 46;   // 116Pd
			case 1204: return 46;   // 117Pd
			case 1205: return 46;   // 118Pd
			case 1206: return 46;   // 119Pd
			case 1207: return 46;   // 120Pd
			case 1208: return 46;   // 121Pd
			case 1209: return 46;   // 122Pd
			case 1210: return 46;   // 123Pd
			case 1211: return 46;   // 124Pd
			case 1212: return 46;   // 125Pd
			case 1213: return 46;   // 126Pd
			case 1214: return 46;   // 127Pd
			case 1215: return 46;   // 128Pd
			case 1216: return 47;   // 93Ag
			case 1217: return 47;   // 94Ag
			case 1218: return 47;   // 95Ag
			case 1219: return 47;   // 96Ag
			case 1220: return 47;   // 97Ag
			case 1221: return 47;   // 98Ag
			case 1222: return 47;   // 99Ag
			case 1223: return 47;   // 100Ag
			case 1224: return 47;   // 101Ag
			case 1225: return 47;   // 102Ag
			case 1226: return 47;   // 103Ag
			case 1227: return 47;   // 104Ag
			case 1228: return 47;   // 105Ag
			case 1229: return 47;   // 106Ag
			case 1230: return 47;   // 107Ag
			case 1231: return 47;   // 108Ag
			case 1232: return 47;   // 109Ag
			case 1233: return 47;   // 110Ag
			case 1234: return 47;   // 111Ag
			case 1235: return 47;   // 112Ag
			case 1236: return 47;   // 113Ag
			case 1237: return 47;   // 114Ag
			case 1238: return 47;   // 115Ag
			case 1239: return 47;   // 116Ag
			case 1240: return 47;   // 117Ag
			case 1241: return 47;   // 118Ag
			case 1242: return 47;   // 119Ag
			case 1243: return 47;   // 120Ag
			case 1244: return 47;   // 121Ag
			case 1245: return 47;   // 122Ag
			case 1246: return 47;   // 123Ag
			case 1247: return 47;   // 124Ag
			case 1248: return 47;   // 125Ag
			case 1249: return 47;   // 126Ag
			case 1250: return 47;   // 127Ag
			case 1251: return 47;   // 128Ag
			case 1252: return 47;   // 129Ag
			case 1253: return 47;   // 130Ag
			case 1254: return 48;   // 95Cd
			case 1255: return 48;   // 96Cd
			case 1256: return 48;   // 97Cd
			case 1257: return 48;   // 98Cd
			case 1258: return 48;   // 99Cd
			case 1259: return 48;   // 100Cd
			case 1260: return 48;   // 101Cd
			case 1261: return 48;   // 102Cd
			case 1262: return 48;   // 103Cd
			case 1263: return 48;   // 104Cd
			case 1264: return 48;   // 105Cd
			case 1265: return 48;   // 106Cd
			case 1266: return 48;   // 107Cd
			case 1267: return 48;   // 108Cd
			case 1268: return 48;   // 109Cd
			case 1269: return 48;   // 110Cd
			case 1270: return 48;   // 111Cd
			case 1271: return 48;   // 112Cd
			case 1272: return 48;   // 113Cd
			case 1273: return 48;   // 114Cd
			case 1274: return 48;   // 115Cd
			case 1275: return 48;   // 116Cd
			case 1276: return 48;   // 117Cd
			case 1277: return 48;   // 118Cd
			case 1278: return 48;   // 119Cd
			case 1279: return 48;   // 120Cd
			case 1280: return 48;   // 121Cd
			case 1281: return 48;   // 122Cd
			case 1282: return 48;   // 123Cd
			case 1283: return 48;   // 124Cd
			case 1284: return 48;   // 125Cd
			case 1285: return 48;   // 126Cd
			case 1286: return 48;   // 127Cd
			case 1287: return 48;   // 128Cd
			case 1288: return 48;   // 129Cd
			case 1289: return 48;   // 130Cd
			case 1290: return 48;   // 131Cd
			case 1291: return 48;   // 132Cd
			case 1292: return 48;   // 133Cd
			case 1293: return 49;   // 97In
			case 1294: return 49;   // 98In
			case 1295: return 49;   // 99In
			case 1296: return 49;   // 100In
			case 1297: return 49;   // 101In
			case 1298: return 49;   // 102In
			case 1299: return 49;   // 103In
			case 1300: return 49;   // 104In
			case 1301: return 49;   // 105In
			case 1302: return 49;   // 106In
			case 1303: return 49;   // 107In
			case 1304: return 49;   // 108In
			case 1305: return 49;   // 109In
			case 1306: return 49;   // 110In
			case 1307: return 49;   // 111In
			case 1308: return 49;   // 112In
			case 1309: return 49;   // 113In
			case 1310: return 49;   // 114In
			case 1311: return 49;   // 115In
			case 1312: return 49;   // 116In
			case 1313: return 49;   // 117In
			case 1314: return 49;   // 118In
			case 1315: return 49;   // 119In
			case 1316: return 49;   // 120In
			case 1317: return 49;   // 121In
			case 1318: return 49;   // 122In
			case 1319: return 49;   // 123In
			case 1320: return 49;   // 124In
			case 1321: return 49;   // 125In
			case 1322: return 49;   // 126In
			case 1323: return 49;   // 127In
			case 1324: return 49;   // 128In
			case 1325: return 49;   // 129In
			case 1326: return 49;   // 130In
			case 1327: return 49;   // 131In
			case 1328: return 49;   // 132In
			case 1329: return 49;   // 133In
			case 1330: return 49;   // 134In
			case 1331: return 49;   // 135In
			case 1332: return 50;   // 99Sn
			case 1333: return 50;   // 100Sn
			case 1334: return 50;   // 101Sn
			case 1335: return 50;   // 102Sn
			case 1336: return 50;   // 103Sn
			case 1337: return 50;   // 104Sn
			case 1338: return 50;   // 105Sn
			case 1339: return 50;   // 106Sn
			case 1340: return 50;   // 107Sn
			case 1341: return 50;   // 108Sn
			case 1342: return 50;   // 109Sn
			case 1343: return 50;   // 110Sn
			case 1344: return 50;   // 111Sn
			case 1345: return 50;   // 112Sn
			case 1346: return 50;   // 113Sn
			case 1347: return 50;   // 114Sn
			case 1348: return 50;   // 115Sn
			case 1349: return 50;   // 116Sn
			case 1350: return 50;   // 117Sn
			case 1351: return 50;   // 118Sn
			case 1352: return 50;   // 119Sn
			case 1353: return 50;   // 120Sn
			case 1354: return 50;   // 121Sn
			case 1355: return 50;   // 122Sn
			case 1356: return 50;   // 123Sn
			case 1357: return 50;   // 124Sn
			case 1358: return 50;   // 125Sn
			case 1359: return 50;   // 126Sn
			case 1360: return 50;   // 127Sn
			case 1361: return 50;   // 128Sn
			case 1362: return 50;   // 129Sn
			case 1363: return 50;   // 130Sn
			case 1364: return 50;   // 131Sn
			case 1365: return 50;   // 132Sn
			case 1366: return 50;   // 133Sn
			case 1367: return 50;   // 134Sn
			case 1368: return 50;   // 135Sn
			case 1369: return 50;   // 136Sn
			case 1370: return 50;   // 137Sn
			case 1371: return 50;   // 138Sn
			case 1372: return 51;   // 103Sb
			case 1373: return 51;   // 104Sb
			case 1374: return 51;   // 105Sb
			case 1375: return 51;   // 106Sb
			case 1376: return 51;   // 107Sb
			case 1377: return 51;   // 108Sb
			case 1378: return 51;   // 109Sb
			case 1379: return 51;   // 110Sb
			case 1380: return 51;   // 111Sb
			case 1381: return 51;   // 112Sb
			case 1382: return 51;   // 113Sb
			case 1383: return 51;   // 114Sb
			case 1384: return 51;   // 115Sb
			case 1385: return 51;   // 116Sb
			case 1386: return 51;   // 117Sb
			case 1387: return 51;   // 118Sb
			case 1388: return 51;   // 119Sb
			case 1389: return 51;   // 120Sb
			case 1390: return 51;   // 121Sb
			case 1391: return 51;   // 122Sb
			case 1392: return 51;   // 123Sb
			case 1393: return 51;   // 124Sb
			case 1394: return 51;   // 125Sb
			case 1395: return 51;   // 126Sb
			case 1396: return 51;   // 127Sb
			case 1397: return 51;   // 128Sb
			case 1398: return 51;   // 129Sb
			case 1399: return 51;   // 130Sb
			case 1400: return 51;   // 131Sb
			case 1401: return 51;   // 132Sb
			case 1402: return 51;   // 133Sb
			case 1403: return 51;   // 134Sb
			case 1404: return 51;   // 135Sb
			case 1405: return 51;   // 136Sb
			case 1406: return 51;   // 137Sb
			case 1407: return 51;   // 138Sb
			case 1408: return 51;   // 139Sb
			case 1409: return 51;   // 140Sb
			case 1410: return 52;   // 105Te
			case 1411: return 52;   // 106Te
			case 1412: return 52;   // 107Te
			case 1413: return 52;   // 108Te
			case 1414: return 52;   // 109Te
			case 1415: return 52;   // 110Te
			case 1416: return 52;   // 111Te
			case 1417: return 52;   // 112Te
			case 1418: return 52;   // 113Te
			case 1419: return 52;   // 114Te
			case 1420: return 52;   // 115Te
			case 1421: return 52;   // 116Te
			case 1422: return 52;   // 117Te
			case 1423: return 52;   // 118Te
			case 1424: return 52;   // 119Te
			case 1425: return 52;   // 120Te
			case 1426: return 52;   // 121Te
			case 1427: return 52;   // 122Te
			case 1428: return 52;   // 123Te
			case 1429: return 52;   // 124Te
			case 1430: return 52;   // 125Te
			case 1431: return 52;   // 126Te
			case 1432: return 52;   // 127Te
			case 1433: return 52;   // 128Te
			case 1434: return 52;   // 129Te
			case 1435: return 52;   // 130Te
			case 1436: return 52;   // 131Te
			case 1437: return 52;   // 132Te
			case 1438: return 52;   // 133Te
			case 1439: return 52;   // 134Te
			case 1440: return 52;   // 135Te
			case 1441: return 52;   // 136Te
			case 1442: return 52;   // 137Te
			case 1443: return 52;   // 138Te
			case 1444: return 52;   // 139Te
			case 1445: return 52;   // 140Te
			case 1446: return 52;   // 141Te
			case 1447: return 52;   // 142Te
			case 1448: return 52;   // 143Te
			case 1449: return 53;   // 107I
			case 1450: return 53;   // 108I
			case 1451: return 53;   // 109I
			case 1452: return 53;   // 110I
			case 1453: return 53;   // 111I
			case 1454: return 53;   // 112I
			case 1455: return 53;   // 113I
			case 1456: return 53;   // 114I
			case 1457: return 53;   // 115I
			case 1458: return 53;   // 116I
			case 1459: return 53;   // 117I
			case 1460: return 53;   // 118I
			case 1461: return 53;   // 119I
			case 1462: return 53;   // 120I
			case 1463: return 53;   // 121I
			case 1464: return 53;   // 122I
			case 1465: return 53;   // 123I
			case 1466: return 53;   // 124I
			case 1467: return 53;   // 125I
			case 1468: return 53;   // 126I
			case 1469: return 53;   // 127I
			case 1470: return 53;   // 128I
			case 1471: return 53;   // 129I
			case 1472: return 53;   // 130I
			case 1473: return 53;   // 131I
			case 1474: return 53;   // 132I
			case 1475: return 53;   // 133I
			case 1476: return 53;   // 134I
			case 1477: return 53;   // 135I
			case 1478: return 53;   // 136I
			case 1479: return 53;   // 137I
			case 1480: return 53;   // 138I
			case 1481: return 53;   // 139I
			case 1482: return 53;   // 140I
			case 1483: return 53;   // 141I
			case 1484: return 53;   // 142I
			case 1485: return 53;   // 143I
			case 1486: return 53;   // 144I
			case 1487: return 53;   // 145I
			case 1488: return 54;   // 109Xe
			case 1489: return 54;   // 110Xe
			case 1490: return 54;   // 111Xe
			case 1491: return 54;   // 112Xe
			case 1492: return 54;   // 113Xe
			case 1493: return 54;   // 114Xe
			case 1494: return 54;   // 115Xe
			case 1495: return 54;   // 116Xe
			case 1496: return 54;   // 117Xe
			case 1497: return 54;   // 118Xe
			case 1498: return 54;   // 119Xe
			case 1499: return 54;   // 120Xe
			case 1500: return 54;   // 121Xe
			case 1501: return 54;   // 122Xe
			case 1502: return 54;   // 123Xe
			case 1503: return 54;   // 124Xe
			case 1504: return 54;   // 125Xe
			case 1505: return 54;   // 126Xe
			case 1506: return 54;   // 127Xe
			case 1507: return 54;   // 128Xe
			case 1508: return 54;   // 129Xe
			case 1509: return 54;   // 130Xe
			case 1510: return 54;   // 131Xe
			case 1511: return 54;   // 132Xe
			case 1512: return 54;   // 133Xe
			case 1513: return 54;   // 134Xe
			case 1514: return 54;   // 135Xe
			case 1515: return 54;   // 136Xe
			case 1516: return 54;   // 137Xe
			case 1517: return 54;   // 138Xe
			case 1518: return 54;   // 139Xe
			case 1519: return 54;   // 140Xe
			case 1520: return 54;   // 141Xe
			case 1521: return 54;   // 142Xe
			case 1522: return 54;   // 143Xe
			case 1523: return 54;   // 144Xe
			case 1524: return 54;   // 145Xe
			case 1525: return 54;   // 146Xe
			case 1526: return 54;   // 147Xe
			case 1527: return 54;   // 148Xe
			case 1528: return 55;   // 112Cs
			case 1529: return 55;   // 113Cs
			case 1530: return 55;   // 114Cs
			case 1531: return 55;   // 115Cs
			case 1532: return 55;   // 116Cs
			case 1533: return 55;   // 117Cs
			case 1534: return 55;   // 118Cs
			case 1535: return 55;   // 119Cs
			case 1536: return 55;   // 120Cs
			case 1537: return 55;   // 121Cs
			case 1538: return 55;   // 122Cs
			case 1539: return 55;   // 123Cs
			case 1540: return 55;   // 124Cs
			case 1541: return 55;   // 125Cs
			case 1542: return 55;   // 126Cs
			case 1543: return 55;   // 127Cs
			case 1544: return 55;   // 128Cs
			case 1545: return 55;   // 129Cs
			case 1546: return 55;   // 130Cs
			case 1547: return 55;   // 131Cs
			case 1548: return 55;   // 132Cs
			case 1549: return 55;   // 133Cs
			case 1550: return 55;   // 134Cs
			case 1551: return 55;   // 135Cs
			case 1552: return 55;   // 136Cs
			case 1553: return 55;   // 137Cs
			case 1554: return 55;   // 138Cs
			case 1555: return 55;   // 139Cs
			case 1556: return 55;   // 140Cs
			case 1557: return 55;   // 141Cs
			case 1558: return 55;   // 142Cs
			case 1559: return 55;   // 143Cs
			case 1560: return 55;   // 144Cs
			case 1561: return 55;   // 145Cs
			case 1562: return 55;   // 146Cs
			case 1563: return 55;   // 147Cs
			case 1564: return 55;   // 148Cs
			case 1565: return 55;   // 149Cs
			case 1566: return 55;   // 150Cs
			case 1567: return 55;   // 151Cs
			case 1568: return 56;   // 114Ba
			case 1569: return 56;   // 115Ba
			case 1570: return 56;   // 116Ba
			case 1571: return 56;   // 117Ba
			case 1572: return 56;   // 118Ba
			case 1573: return 56;   // 119Ba
			case 1574: return 56;   // 120Ba
			case 1575: return 56;   // 121Ba
			case 1576: return 56;   // 122Ba
			case 1577: return 56;   // 123Ba
			case 1578: return 56;   // 124Ba
			case 1579: return 56;   // 125Ba
			case 1580: return 56;   // 126Ba
			case 1581: return 56;   // 127Ba
			case 1582: return 56;   // 128Ba
			case 1583: return 56;   // 129Ba
			case 1584: return 56;   // 130Ba
			case 1585: return 56;   // 131Ba
			case 1586: return 56;   // 132Ba
			case 1587: return 56;   // 133Ba
			case 1588: return 56;   // 134Ba
			case 1589: return 56;   // 135Ba
			case 1590: return 56;   // 136Ba
			case 1591: return 56;   // 137Ba
			case 1592: return 56;   // 138Ba
			case 1593: return 56;   // 139Ba
			case 1594: return 56;   // 140Ba
			case 1595: return 56;   // 141Ba
			case 1596: return 56;   // 142Ba
			case 1597: return 56;   // 143Ba
			case 1598: return 56;   // 144Ba
			case 1599: return 56;   // 145Ba
			case 1600: return 56;   // 146Ba
			case 1601: return 56;   // 147Ba
			case 1602: return 56;   // 148Ba
			case 1603: return 56;   // 149Ba
			case 1604: return 56;   // 150Ba
			case 1605: return 56;   // 151Ba
			case 1606: return 56;   // 152Ba
			case 1607: return 56;   // 153Ba
			case 1608: return 57;   // 116La
			case 1609: return 57;   // 117La
			case 1610: return 57;   // 118La
			case 1611: return 57;   // 119La
			case 1612: return 57;   // 120La
			case 1613: return 57;   // 121La
			case 1614: return 57;   // 122La
			case 1615: return 57;   // 123La
			case 1616: return 57;   // 124La
			case 1617: return 57;   // 125La
			case 1618: return 57;   // 126La
			case 1619: return 57;   // 127La
			case 1620: return 57;   // 128La
			case 1621: return 57;   // 129La
			case 1622: return 57;   // 130La
			case 1623: return 57;   // 131La
			case 1624: return 57;   // 132La
			case 1625: return 57;   // 133La
			case 1626: return 57;   // 134La
			case 1627: return 57;   // 135La
			case 1628: return 57;   // 136La
			case 1629: return 57;   // 137La
			case 1630: return 57;   // 138La
			case 1631: return 57;   // 139La
			case 1632: return 57;   // 140La
			case 1633: return 57;   // 141La
			case 1634: return 57;   // 142La
			case 1635: return 57;   // 143La
			case 1636: return 57;   // 144La
			case 1637: return 57;   // 145La
			case 1638: return 57;   // 146La
			case 1639: return 57;   // 147La
			case 1640: return 57;   // 148La
			case 1641: return 57;   // 149La
			case 1642: return 57;   // 150La
			case 1643: return 57;   // 151La
			case 1644: return 57;   // 152La
			case 1645: return 57;   // 153La
			case 1646: return 57;   // 154La
			case 1647: return 57;   // 155La
			case 1648: return 58;   // 119Ce
			case 1649: return 58;   // 120Ce
			case 1650: return 58;   // 121Ce
			case 1651: return 58;   // 122Ce
			case 1652: return 58;   // 123Ce
			case 1653: return 58;   // 124Ce
			case 1654: return 58;   // 125Ce
			case 1655: return 58;   // 126Ce
			case 1656: return 58;   // 127Ce
			case 1657: return 58;   // 128Ce
			case 1658: return 58;   // 129Ce
			case 1659: return 58;   // 130Ce
			case 1660: return 58;   // 131Ce
			case 1661: return 58;   // 132Ce
			case 1662: return 58;   // 133Ce
			case 1663: return 58;   // 134Ce
			case 1664: return 58;   // 135Ce
			case 1665: return 58;   // 136Ce
			case 1666: return 58;   // 137Ce
			case 1667: return 58;   // 138Ce
			case 1668: return 58;   // 139Ce
			case 1669: return 58;   // 140Ce
			case 1670: return 58;   // 141Ce
			case 1671: return 58;   // 142Ce
			case 1672: return 58;   // 143Ce
			case 1673: return 58;   // 144Ce
			case 1674: return 58;   // 145Ce
			case 1675: return 58;   // 146Ce
			case 1676: return 58;   // 147Ce
			case 1677: return 58;   // 148Ce
			case 1678: return 58;   // 149Ce
			case 1679: return 58;   // 150Ce
			case 1680: return 58;   // 151Ce
			case 1681: return 58;   // 152Ce
			case 1682: return 58;   // 153Ce
			case 1683: return 58;   // 154Ce
			case 1684: return 58;   // 155Ce
			case 1685: return 58;   // 156Ce
			case 1686: return 58;   // 157Ce
			case 1687: return 59;   // 121Pr
			case 1688: return 59;   // 122Pr
			case 1689: return 59;   // 123Pr
			case 1690: return 59;   // 124Pr
			case 1691: return 59;   // 125Pr
			case 1692: return 59;   // 126Pr
			case 1693: return 59;   // 127Pr
			case 1694: return 59;   // 128Pr
			case 1695: return 59;   // 129Pr
			case 1696: return 59;   // 130Pr
			case 1697: return 59;   // 131Pr
			case 1698: return 59;   // 132Pr
			case 1699: return 59;   // 133Pr
			case 1700: return 59;   // 134Pr
			case 1701: return 59;   // 135Pr
			case 1702: return 59;   // 136Pr
			case 1703: return 59;   // 137Pr
			case 1704: return 59;   // 138Pr
			case 1705: return 59;   // 139Pr
			case 1706: return 59;   // 140Pr
			case 1707: return 59;   // 141Pr
			case 1708: return 59;   // 142Pr
			case 1709: return 59;   // 143Pr
			case 1710: return 59;   // 144Pr
			case 1711: return 59;   // 145Pr
			case 1712: return 59;   // 146Pr
			case 1713: return 59;   // 147Pr
			case 1714: return 59;   // 148Pr
			case 1715: return 59;   // 149Pr
			case 1716: return 59;   // 150Pr
			case 1717: return 59;   // 151Pr
			case 1718: return 59;   // 152Pr
			case 1719: return 59;   // 153Pr
			case 1720: return 59;   // 154Pr
			case 1721: return 59;   // 155Pr
			case 1722: return 59;   // 156Pr
			case 1723: return 59;   // 157Pr
			case 1724: return 59;   // 158Pr
			case 1725: return 59;   // 159Pr
			case 1726: return 60;   // 124Nd
			case 1727: return 60;   // 125Nd
			case 1728: return 60;   // 126Nd
			case 1729: return 60;   // 127Nd
			case 1730: return 60;   // 128Nd
			case 1731: return 60;   // 129Nd
			case 1732: return 60;   // 130Nd
			case 1733: return 60;   // 131Nd
			case 1734: return 60;   // 132Nd
			case 1735: return 60;   // 133Nd
			case 1736: return 60;   // 134Nd
			case 1737: return 60;   // 135Nd
			case 1738: return 60;   // 136Nd
			case 1739: return 60;   // 137Nd
			case 1740: return 60;   // 138Nd
			case 1741: return 60;   // 139Nd
			case 1742: return 60;   // 140Nd
			case 1743: return 60;   // 141Nd
			case 1744: return 60;   // 142Nd
			case 1745: return 60;   // 143Nd
			case 1746: return 60;   // 144Nd
			case 1747: return 60;   // 145Nd
			case 1748: return 60;   // 146Nd
			case 1749: return 60;   // 147Nd
			case 1750: return 60;   // 148Nd
			case 1751: return 60;   // 149Nd
			case 1752: return 60;   // 150Nd
			case 1753: return 60;   // 151Nd
			case 1754: return 60;   // 152Nd
			case 1755: return 60;   // 153Nd
			case 1756: return 60;   // 154Nd
			case 1757: return 60;   // 155Nd
			case 1758: return 60;   // 156Nd
			case 1759: return 60;   // 157Nd
			case 1760: return 60;   // 158Nd
			case 1761: return 60;   // 159Nd
			case 1762: return 60;   // 160Nd
			case 1763: return 60;   // 161Nd
			case 1764: return 61;   // 126Pm
			case 1765: return 61;   // 127Pm
			case 1766: return 61;   // 128Pm
			case 1767: return 61;   // 129Pm
			case 1768: return 61;   // 130Pm
			case 1769: return 61;   // 131Pm
			case 1770: return 61;   // 132Pm
			case 1771: return 61;   // 133Pm
			case 1772: return 61;   // 134Pm
			case 1773: return 61;   // 135Pm
			case 1774: return 61;   // 136Pm
			case 1775: return 61;   // 137Pm
			case 1776: return 61;   // 138Pm
			case 1777: return 61;   // 139Pm
			case 1778: return 61;   // 140Pm
			case 1779: return 61;   // 141Pm
			case 1780: return 61;   // 142Pm
			case 1781: return 61;   // 143Pm
			case 1782: return 61;   // 144Pm
			case 1783: return 61;   // 145Pm
			case 1784: return 61;   // 146Pm
			case 1785: return 61;   // 147Pm
			case 1786: return 61;   // 148Pm
			case 1787: return 61;   // 149Pm
			case 1788: return 61;   // 150Pm
			case 1789: return 61;   // 151Pm
			case 1790: return 61;   // 152Pm
			case 1791: return 61;   // 153Pm
			case 1792: return 61;   // 154Pm
			case 1793: return 61;   // 155Pm
			case 1794: return 61;   // 156Pm
			case 1795: return 61;   // 157Pm
			case 1796: return 61;   // 158Pm
			case 1797: return 61;   // 159Pm
			case 1798: return 61;   // 160Pm
			case 1799: return 61;   // 161Pm
			case 1800: return 61;   // 162Pm
			case 1801: return 61;   // 163Pm
			case 1802: return 62;   // 128Sm
			case 1803: return 62;   // 129Sm
			case 1804: return 62;   // 130Sm
			case 1805: return 62;   // 131Sm
			case 1806: return 62;   // 132Sm
			case 1807: return 62;   // 133Sm
			case 1808: return 62;   // 134Sm
			case 1809: return 62;   // 135Sm
			case 1810: return 62;   // 136Sm
			case 1811: return 62;   // 137Sm
			case 1812: return 62;   // 138Sm
			case 1813: return 62;   // 139Sm
			case 1814: return 62;   // 140Sm
			case 1815: return 62;   // 141Sm
			case 1816: return 62;   // 142Sm
			case 1817: return 62;   // 143Sm
			case 1818: return 62;   // 144Sm
			case 1819: return 62;   // 145Sm
			case 1820: return 62;   // 146Sm
			case 1821: return 62;   // 147Sm
			case 1822: return 62;   // 148Sm
			case 1823: return 62;   // 149Sm
			case 1824: return 62;   // 150Sm
			case 1825: return 62;   // 151Sm
			case 1826: return 62;   // 152Sm
			case 1827: return 62;   // 153Sm
			case 1828: return 62;   // 154Sm
			case 1829: return 62;   // 155Sm
			case 1830: return 62;   // 156Sm
			case 1831: return 62;   // 157Sm
			case 1832: return 62;   // 158Sm
			case 1833: return 62;   // 159Sm
			case 1834: return 62;   // 160Sm
			case 1835: return 62;   // 161Sm
			case 1836: return 62;   // 162Sm
			case 1837: return 62;   // 163Sm
			case 1838: return 62;   // 164Sm
			case 1839: return 62;   // 165Sm
			case 1840: return 63;   // 130Eu
			case 1841: return 63;   // 131Eu
			case 1842: return 63;   // 132Eu
			case 1843: return 63;   // 133Eu
			case 1844: return 63;   // 134Eu
			case 1845: return 63;   // 135Eu
			case 1846: return 63;   // 136Eu
			case 1847: return 63;   // 137Eu
			case 1848: return 63;   // 138Eu
			case 1849: return 63;   // 139Eu
			case 1850: return 63;   // 140Eu
			case 1851: return 63;   // 141Eu
			case 1852: return 63;   // 142Eu
			case 1853: return 63;   // 143Eu
			case 1854: return 63;   // 144Eu
			case 1855: return 63;   // 145Eu
			case 1856: return 63;   // 146Eu
			case 1857: return 63;   // 147Eu
			case 1858: return 63;   // 148Eu
			case 1859: return 63;   // 149Eu
			case 1860: return 63;   // 150Eu
			case 1861: return 63;   // 151Eu
			case 1862: return 63;   // 152Eu
			case 1863: return 63;   // 153Eu
			case 1864: return 63;   // 154Eu
			case 1865: return 63;   // 155Eu
			case 1866: return 63;   // 156Eu
			case 1867: return 63;   // 157Eu
			case 1868: return 63;   // 158Eu
			case 1869: return 63;   // 159Eu
			case 1870: return 63;   // 160Eu
			case 1871: return 63;   // 161Eu
			case 1872: return 63;   // 162Eu
			case 1873: return 63;   // 163Eu
			case 1874: return 63;   // 164Eu
			case 1875: return 63;   // 165Eu
			case 1876: return 63;   // 166Eu
			case 1877: return 63;   // 167Eu
			case 1878: return 64;   // 133Gd
			case 1879: return 64;   // 134Gd
			case 1880: return 64;   // 135Gd
			case 1881: return 64;   // 136Gd
			case 1882: return 64;   // 137Gd
			case 1883: return 64;   // 138Gd
			case 1884: return 64;   // 139Gd
			case 1885: return 64;   // 140Gd
			case 1886: return 64;   // 141Gd
			case 1887: return 64;   // 142Gd
			case 1888: return 64;   // 143Gd
			case 1889: return 64;   // 144Gd
			case 1890: return 64;   // 145Gd
			case 1891: return 64;   // 146Gd
			case 1892: return 64;   // 147Gd
			case 1893: return 64;   // 148Gd
			case 1894: return 64;   // 149Gd
			case 1895: return 64;   // 150Gd
			case 1896: return 64;   // 151Gd
			case 1897: return 64;   // 152Gd
			case 1898: return 64;   // 153Gd
			case 1899: return 64;   // 154Gd
			case 1900: return 64;   // 155Gd
			case 1901: return 64;   // 156Gd
			case 1902: return 64;   // 157Gd
			case 1903: return 64;   // 158Gd
			case 1904: return 64;   // 159Gd
			case 1905: return 64;   // 160Gd
			case 1906: return 64;   // 161Gd
			case 1907: return 64;   // 162Gd
			case 1908: return 64;   // 163Gd
			case 1909: return 64;   // 164Gd
			case 1910: return 64;   // 165Gd
			case 1911: return 64;   // 166Gd
			case 1912: return 64;   // 167Gd
			case 1913: return 64;   // 168Gd
			case 1914: return 64;   // 169Gd
			case 1915: return 65;   // 135Tb
			case 1916: return 65;   // 136Tb
			case 1917: return 65;   // 137Tb
			case 1918: return 65;   // 138Tb
			case 1919: return 65;   // 139Tb
			case 1920: return 65;   // 140Tb
			case 1921: return 65;   // 141Tb
			case 1922: return 65;   // 142Tb
			case 1923: return 65;   // 143Tb
			case 1924: return 65;   // 144Tb
			case 1925: return 65;   // 145Tb
			case 1926: return 65;   // 146Tb
			case 1927: return 65;   // 147Tb
			case 1928: return 65;   // 148Tb
			case 1929: return 65;   // 149Tb
			case 1930: return 65;   // 150Tb
			case 1931: return 65;   // 151Tb
			case 1932: return 65;   // 152Tb
			case 1933: return 65;   // 153Tb
			case 1934: return 65;   // 154Tb
			case 1935: return 65;   // 155Tb
			case 1936: return 65;   // 156Tb
			case 1937: return 65;   // 157Tb
			case 1938: return 65;   // 158Tb
			case 1939: return 65;   // 159Tb
			case 1940: return 65;   // 160Tb
			case 1941: return 65;   // 161Tb
			case 1942: return 65;   // 162Tb
			case 1943: return 65;   // 163Tb
			case 1944: return 65;   // 164Tb
			case 1945: return 65;   // 165Tb
			case 1946: return 65;   // 166Tb
			case 1947: return 65;   // 167Tb
			case 1948: return 65;   // 168Tb
			case 1949: return 65;   // 169Tb
			case 1950: return 65;   // 170Tb
			case 1951: return 65;   // 171Tb
			case 1952: return 66;   // 138Dy
			case 1953: return 66;   // 139Dy
			case 1954: return 66;   // 140Dy
			case 1955: return 66;   // 141Dy
			case 1956: return 66;   // 142Dy
			case 1957: return 66;   // 143Dy
			case 1958: return 66;   // 144Dy
			case 1959: return 66;   // 145Dy
			case 1960: return 66;   // 146Dy
			case 1961: return 66;   // 147Dy
			case 1962: return 66;   // 148Dy
			case 1963: return 66;   // 149Dy
			case 1964: return 66;   // 150Dy
			case 1965: return 66;   // 151Dy
			case 1966: return 66;   // 152Dy
			case 1967: return 66;   // 153Dy
			case 1968: return 66;   // 154Dy
			case 1969: return 66;   // 155Dy
			case 1970: return 66;   // 156Dy
			case 1971: return 66;   // 157Dy
			case 1972: return 66;   // 158Dy
			case 1973: return 66;   // 159Dy
			case 1974: return 66;   // 160Dy
			case 1975: return 66;   // 161Dy
			case 1976: return 66;   // 162Dy
			case 1977: return 66;   // 163Dy
			case 1978: return 66;   // 164Dy
			case 1979: return 66;   // 165Dy
			case 1980: return 66;   // 166Dy
			case 1981: return 66;   // 167Dy
			case 1982: return 66;   // 168Dy
			case 1983: return 66;   // 169Dy
			case 1984: return 66;   // 170Dy
			case 1985: return 66;   // 171Dy
			case 1986: return 66;   // 172Dy
			case 1987: return 66;   // 173Dy
			case 1988: return 67;   // 140Ho
			case 1989: return 67;   // 141Ho
			case 1990: return 67;   // 142Ho
			case 1991: return 67;   // 143Ho
			case 1992: return 67;   // 144Ho
			case 1993: return 67;   // 145Ho
			case 1994: return 67;   // 146Ho
			case 1995: return 67;   // 147Ho
			case 1996: return 67;   // 148Ho
			case 1997: return 67;   // 149Ho
			case 1998: return 67;   // 150Ho
			case 1999: return 67;   // 151Ho
			case 2000: return 67;   // 152Ho
			case 2001: return 67;   // 153Ho
			case 2002: return 67;   // 154Ho
			case 2003: return 67;   // 155Ho
			case 2004: return 67;   // 156Ho
			case 2005: return 67;   // 157Ho
			case 2006: return 67;   // 158Ho
			case 2007: return 67;   // 159Ho
			case 2008: return 67;   // 160Ho
			case 2009: return 67;   // 161Ho
			case 2010: return 67;   // 162Ho
			case 2011: return 67;   // 163Ho
			case 2012: return 67;   // 164Ho
			case 2013: return 67;   // 165Ho
			case 2014: return 67;   // 166Ho
			case 2015: return 67;   // 167Ho
			case 2016: return 67;   // 168Ho
			case 2017: return 67;   // 169Ho
			case 2018: return 67;   // 170Ho
			case 2019: return 67;   // 171Ho
			case 2020: return 67;   // 172Ho
			case 2021: return 67;   // 173Ho
			case 2022: return 67;   // 174Ho
			case 2023: return 67;   // 175Ho
			case 2024: return 68;   // 142Er
			case 2025: return 68;   // 143Er
			case 2026: return 68;   // 144Er
			case 2027: return 68;   // 145Er
			case 2028: return 68;   // 146Er
			case 2029: return 68;   // 147Er
			case 2030: return 68;   // 148Er
			case 2031: return 68;   // 149Er
			case 2032: return 68;   // 150Er
			case 2033: return 68;   // 151Er
			case 2034: return 68;   // 152Er
			case 2035: return 68;   // 153Er
			case 2036: return 68;   // 154Er
			case 2037: return 68;   // 155Er
			case 2038: return 68;   // 156Er
			case 2039: return 68;   // 157Er
			case 2040: return 68;   // 158Er
			case 2041: return 68;   // 159Er
			case 2042: return 68;   // 160Er
			case 2043: return 68;   // 161Er
			case 2044: return 68;   // 162Er
			case 2045: return 68;   // 163Er
			case 2046: return 68;   // 164Er
			case 2047: return 68;   // 165Er
			case 2048: return 68;   // 166Er
			case 2049: return 68;   // 167Er
			case 2050: return 68;   // 168Er
			case 2051: return 68;   // 169Er
			case 2052: return 68;   // 170Er
			case 2053: return 68;   // 171Er
			case 2054: return 68;   // 172Er
			case 2055: return 68;   // 173Er
			case 2056: return 68;   // 174Er
			case 2057: return 68;   // 175Er
			case 2058: return 68;   // 176Er
			case 2059: return 68;   // 177Er
			case 2060: return 69;   // 144Tm
			case 2061: return 69;   // 145Tm
			case 2062: return 69;   // 146Tm
			case 2063: return 69;   // 147Tm
			case 2064: return 69;   // 148Tm
			case 2065: return 69;   // 149Tm
			case 2066: return 69;   // 150Tm
			case 2067: return 69;   // 151Tm
			case 2068: return 69;   // 152Tm
			case 2069: return 69;   // 153Tm
			case 2070: return 69;   // 154Tm
			case 2071: return 69;   // 155Tm
			case 2072: return 69;   // 156Tm
			case 2073: return 69;   // 157Tm
			case 2074: return 69;   // 158Tm
			case 2075: return 69;   // 159Tm
			case 2076: return 69;   // 160Tm
			case 2077: return 69;   // 161Tm
			case 2078: return 69;   // 162Tm
			case 2079: return 69;   // 163Tm
			case 2080: return 69;   // 164Tm
			case 2081: return 69;   // 165Tm
			case 2082: return 69;   // 166Tm
			case 2083: return 69;   // 167Tm
			case 2084: return 69;   // 168Tm
			case 2085: return 69;   // 169Tm
			case 2086: return 69;   // 170Tm
			case 2087: return 69;   // 171Tm
			case 2088: return 69;   // 172Tm
			case 2089: return 69;   // 173Tm
			case 2090: return 69;   // 174Tm
			case 2091: return 69;   // 175Tm
			case 2092: return 69;   // 176Tm
			case 2093: return 69;   // 177Tm
			case 2094: return 69;   // 178Tm
			case 2095: return 69;   // 179Tm
			case 2096: return 70;   // 148Yb
			case 2097: return 70;   // 149Yb
			case 2098: return 70;   // 150Yb
			case 2099: return 70;   // 151Yb
			case 2100: return 70;   // 152Yb
			case 2101: return 70;   // 153Yb
			case 2102: return 70;   // 154Yb
			case 2103: return 70;   // 155Yb
			case 2104: return 70;   // 156Yb
			case 2105: return 70;   // 157Yb
			case 2106: return 70;   // 158Yb
			case 2107: return 70;   // 159Yb
			case 2108: return 70;   // 160Yb
			case 2109: return 70;   // 161Yb
			case 2110: return 70;   // 162Yb
			case 2111: return 70;   // 163Yb
			case 2112: return 70;   // 164Yb
			case 2113: return 70;   // 165Yb
			case 2114: return 70;   // 166Yb
			case 2115: return 70;   // 167Yb
			case 2116: return 70;   // 168Yb
			case 2117: return 70;   // 169Yb
			case 2118: return 70;   // 170Yb
			case 2119: return 70;   // 171Yb
			case 2120: return 70;   // 172Yb
			case 2121: return 70;   // 173Yb
			case 2122: return 70;   // 174Yb
			case 2123: return 70;   // 175Yb
			case 2124: return 70;   // 176Yb
			case 2125: return 70;   // 177Yb
			case 2126: return 70;   // 178Yb
			case 2127: return 70;   // 179Yb
			case 2128: return 70;   // 180Yb
			case 2129: return 70;   // 181Yb
			case 2130: return 71;   // 150Lu
			case 2131: return 71;   // 151Lu
			case 2132: return 71;   // 152Lu
			case 2133: return 71;   // 153Lu
			case 2134: return 71;   // 154Lu
			case 2135: return 71;   // 155Lu
			case 2136: return 71;   // 156Lu
			case 2137: return 71;   // 157Lu
			case 2138: return 71;   // 158Lu
			case 2139: return 71;   // 159Lu
			case 2140: return 71;   // 160Lu
			case 2141: return 71;   // 161Lu
			case 2142: return 71;   // 162Lu
			case 2143: return 71;   // 163Lu
			case 2144: return 71;   // 164Lu
			case 2145: return 71;   // 165Lu
			case 2146: return 71;   // 166Lu
			case 2147: return 71;   // 167Lu
			case 2148: return 71;   // 168Lu
			case 2149: return 71;   // 169Lu
			case 2150: return 71;   // 170Lu
			case 2151: return 71;   // 171Lu
			case 2152: return 71;   // 172Lu
			case 2153: return 71;   // 173Lu
			case 2154: return 71;   // 174Lu
			case 2155: return 71;   // 175Lu
			case 2156: return 71;   // 176Lu
			case 2157: return 71;   // 177Lu
			case 2158: return 71;   // 178Lu
			case 2159: return 71;   // 179Lu
			case 2160: return 71;   // 180Lu
			case 2161: return 71;   // 181Lu
			case 2162: return 71;   // 182Lu
			case 2163: return 71;   // 183Lu
			case 2164: return 71;   // 184Lu
			case 2165: return 71;   // 185Lu
			case 2166: return 72;   // 153Hf
			case 2167: return 72;   // 154Hf
			case 2168: return 72;   // 155Hf
			case 2169: return 72;   // 156Hf
			case 2170: return 72;   // 157Hf
			case 2171: return 72;   // 158Hf
			case 2172: return 72;   // 159Hf
			case 2173: return 72;   // 160Hf
			case 2174: return 72;   // 161Hf
			case 2175: return 72;   // 162Hf
			case 2176: return 72;   // 163Hf
			case 2177: return 72;   // 164Hf
			case 2178: return 72;   // 165Hf
			case 2179: return 72;   // 166Hf
			case 2180: return 72;   // 167Hf
			case 2181: return 72;   // 168Hf
			case 2182: return 72;   // 169Hf
			case 2183: return 72;   // 170Hf
			case 2184: return 72;   // 171Hf
			case 2185: return 72;   // 172Hf
			case 2186: return 72;   // 173Hf
			case 2187: return 72;   // 174Hf
			case 2188: return 72;   // 175Hf
			case 2189: return 72;   // 176Hf
			case 2190: return 72;   // 177Hf
			case 2191: return 72;   // 178Hf
			case 2192: return 72;   // 179Hf
			case 2193: return 72;   // 180Hf
			case 2194: return 72;   // 181Hf
			case 2195: return 72;   // 182Hf
			case 2196: return 72;   // 183Hf
			case 2197: return 72;   // 184Hf
			case 2198: return 72;   // 185Hf
			case 2199: return 72;   // 186Hf
			case 2200: return 72;   // 187Hf
			case 2201: return 72;   // 188Hf
			case 2202: return 72;   // 189Hf
			case 2203: return 73;   // 155Ta
			case 2204: return 73;   // 156Ta
			case 2205: return 73;   // 157Ta
			case 2206: return 73;   // 158Ta
			case 2207: return 73;   // 159Ta
			case 2208: return 73;   // 160Ta
			case 2209: return 73;   // 161Ta
			case 2210: return 73;   // 162Ta
			case 2211: return 73;   // 163Ta
			case 2212: return 73;   // 164Ta
			case 2213: return 73;   // 165Ta
			case 2214: return 73;   // 166Ta
			case 2215: return 73;   // 167Ta
			case 2216: return 73;   // 168Ta
			case 2217: return 73;   // 169Ta
			case 2218: return 73;   // 170Ta
			case 2219: return 73;   // 171Ta
			case 2220: return 73;   // 172Ta
			case 2221: return 73;   // 173Ta
			case 2222: return 73;   // 174Ta
			case 2223: return 73;   // 175Ta
			case 2224: return 73;   // 176Ta
			case 2225: return 73;   // 177Ta
			case 2226: return 73;   // 178Ta
			case 2227: return 73;   // 179Ta
			case 2228: return 73;   // 180Ta
			case 2229: return 73;   // 181Ta
			case 2230: return 73;   // 182Ta
			case 2231: return 73;   // 183Ta
			case 2232: return 73;   // 184Ta
			case 2233: return 73;   // 185Ta
			case 2234: return 73;   // 186Ta
			case 2235: return 73;   // 187Ta
			case 2236: return 73;   // 188Ta
			case 2237: return 73;   // 189Ta
			case 2238: return 73;   // 190Ta
			case 2239: return 73;   // 191Ta
			case 2240: return 73;   // 192Ta
			case 2241: return 74;   // 157W
			case 2242: return 74;   // 158W
			case 2243: return 74;   // 159W
			case 2244: return 74;   // 160W
			case 2245: return 74;   // 161W
			case 2246: return 74;   // 162W
			case 2247: return 74;   // 163W
			case 2248: return 74;   // 164W
			case 2249: return 74;   // 165W
			case 2250: return 74;   // 166W
			case 2251: return 74;   // 167W
			case 2252: return 74;   // 168W
			case 2253: return 74;   // 169W
			case 2254: return 74;   // 170W
			case 2255: return 74;   // 171W
			case 2256: return 74;   // 172W
			case 2257: return 74;   // 173W
			case 2258: return 74;   // 174W
			case 2259: return 74;   // 175W
			case 2260: return 74;   // 176W
			case 2261: return 74;   // 177W
			case 2262: return 74;   // 178W
			case 2263: return 74;   // 179W
			case 2264: return 74;   // 180W
			case 2265: return 74;   // 181W
			case 2266: return 74;   // 182W
			case 2267: return 74;   // 183W
			case 2268: return 74;   // 184W
			case 2269: return 74;   // 185W
			case 2270: return 74;   // 186W
			case 2271: return 74;   // 187W
			case 2272: return 74;   // 188W
			case 2273: return 74;   // 189W
			case 2274: return 74;   // 190W
			case 2275: return 74;   // 191W
			case 2276: return 74;   // 192W
			case 2277: return 74;   // 193W
			case 2278: return 74;   // 194W
			case 2279: return 75;   // 159Re
			case 2280: return 75;   // 160Re
			case 2281: return 75;   // 161Re
			case 2282: return 75;   // 162Re
			case 2283: return 75;   // 163Re
			case 2284: return 75;   // 164Re
			case 2285: return 75;   // 165Re
			case 2286: return 75;   // 166Re
			case 2287: return 75;   // 167Re
			case 2288: return 75;   // 168Re
			case 2289: return 75;   // 169Re
			case 2290: return 75;   // 170Re
			case 2291: return 75;   // 171Re
			case 2292: return 75;   // 172Re
			case 2293: return 75;   // 173Re
			case 2294: return 75;   // 174Re
			case 2295: return 75;   // 175Re
			case 2296: return 75;   // 176Re
			case 2297: return 75;   // 177Re
			case 2298: return 75;   // 178Re
			case 2299: return 75;   // 179Re
			case 2300: return 75;   // 180Re
			case 2301: return 75;   // 181Re
			case 2302: return 75;   // 182Re
			case 2303: return 75;   // 183Re
			case 2304: return 75;   // 184Re
			case 2305: return 75;   // 185Re
			case 2306: return 75;   // 186Re
			case 2307: return 75;   // 187Re
			case 2308: return 75;   // 188Re
			case 2309: return 75;   // 189Re
			case 2310: return 75;   // 190Re
			case 2311: return 75;   // 191Re
			case 2312: return 75;   // 192Re
			case 2313: return 75;   // 193Re
			case 2314: return 75;   // 194Re
			case 2315: return 75;   // 195Re
			case 2316: return 75;   // 196Re
			case 2317: return 75;   // 197Re
			case 2318: return 75;   // 198Re
			case 2319: return 76;   // 161Os
			case 2320: return 76;   // 162Os
			case 2321: return 76;   // 163Os
			case 2322: return 76;   // 164Os
			case 2323: return 76;   // 165Os
			case 2324: return 76;   // 166Os
			case 2325: return 76;   // 167Os
			case 2326: return 76;   // 168Os
			case 2327: return 76;   // 169Os
			case 2328: return 76;   // 170Os
			case 2329: return 76;   // 171Os
			case 2330: return 76;   // 172Os
			case 2331: return 76;   // 173Os
			case 2332: return 76;   // 174Os
			case 2333: return 76;   // 175Os
			case 2334: return 76;   // 176Os
			case 2335: return 76;   // 177Os
			case 2336: return 76;   // 178Os
			case 2337: return 76;   // 179Os
			case 2338: return 76;   // 180Os
			case 2339: return 76;   // 181Os
			case 2340: return 76;   // 182Os
			case 2341: return 76;   // 183Os
			case 2342: return 76;   // 184Os
			case 2343: return 76;   // 185Os
			case 2344: return 76;   // 186Os
			case 2345: return 76;   // 187Os
			case 2346: return 76;   // 188Os
			case 2347: return 76;   // 189Os
			case 2348: return 76;   // 190Os
			case 2349: return 76;   // 191Os
			case 2350: return 76;   // 192Os
			case 2351: return 76;   // 193Os
			case 2352: return 76;   // 194Os
			case 2353: return 76;   // 195Os
			case 2354: return 76;   // 196Os
			case 2355: return 76;   // 197Os
			case 2356: return 76;   // 198Os
			case 2357: return 76;   // 199Os
			case 2358: return 76;   // 200Os
			case 2359: return 76;   // 201Os
			case 2360: return 76;   // 202Os
			case 2361: return 77;   // 164Ir
			case 2362: return 77;   // 165Ir
			case 2363: return 77;   // 166Ir
			case 2364: return 77;   // 167Ir
			case 2365: return 77;   // 168Ir
			case 2366: return 77;   // 169Ir
			case 2367: return 77;   // 170Ir
			case 2368: return 77;   // 171Ir
			case 2369: return 77;   // 172Ir
			case 2370: return 77;   // 173Ir
			case 2371: return 77;   // 174Ir
			case 2372: return 77;   // 175Ir
			case 2373: return 77;   // 176Ir
			case 2374: return 77;   // 177Ir
			case 2375: return 77;   // 178Ir
			case 2376: return 77;   // 179Ir
			case 2377: return 77;   // 180Ir
			case 2378: return 77;   // 181Ir
			case 2379: return 77;   // 182Ir
			case 2380: return 77;   // 183Ir
			case 2381: return 77;   // 184Ir
			case 2382: return 77;   // 185Ir
			case 2383: return 77;   // 186Ir
			case 2384: return 77;   // 187Ir
			case 2385: return 77;   // 188Ir
			case 2386: return 77;   // 189Ir
			case 2387: return 77;   // 190Ir
			case 2388: return 77;   // 191Ir
			case 2389: return 77;   // 192Ir
			case 2390: return 77;   // 193Ir
			case 2391: return 77;   // 194Ir
			case 2392: return 77;   // 195Ir
			case 2393: return 77;   // 196Ir
			case 2394: return 77;   // 197Ir
			case 2395: return 77;   // 198Ir
			case 2396: return 77;   // 199Ir
			case 2397: return 77;   // 200Ir
			case 2398: return 77;   // 201Ir
			case 2399: return 77;   // 202Ir
			case 2400: return 77;   // 203Ir
			case 2401: return 77;   // 204Ir
			case 2402: return 78;   // 166Pt
			case 2403: return 78;   // 167Pt
			case 2404: return 78;   // 168Pt
			case 2405: return 78;   // 169Pt
			case 2406: return 78;   // 170Pt
			case 2407: return 78;   // 171Pt
			case 2408: return 78;   // 172Pt
			case 2409: return 78;   // 173Pt
			case 2410: return 78;   // 174Pt
			case 2411: return 78;   // 175Pt
			case 2412: return 78;   // 176Pt
			case 2413: return 78;   // 177Pt
			case 2414: return 78;   // 178Pt
			case 2415: return 78;   // 179Pt
			case 2416: return 78;   // 180Pt
			case 2417: return 78;   // 181Pt
			case 2418: return 78;   // 182Pt
			case 2419: return 78;   // 183Pt
			case 2420: return 78;   // 184Pt
			case 2421: return 78;   // 185Pt
			case 2422: return 78;   // 186Pt
			case 2423: return 78;   // 187Pt
			case 2424: return 78;   // 188Pt
			case 2425: return 78;   // 189Pt
			case 2426: return 78;   // 190Pt
			case 2427: return 78;   // 191Pt
			case 2428: return 78;   // 192Pt
			case 2429: return 78;   // 193Pt
			case 2430: return 78;   // 194Pt
			case 2431: return 78;   // 195Pt
			case 2432: return 78;   // 196Pt
			case 2433: return 78;   // 197Pt
			case 2434: return 78;   // 198Pt
			case 2435: return 78;   // 199Pt
			case 2436: return 78;   // 200Pt
			case 2437: return 78;   // 201Pt
			case 2438: return 78;   // 202Pt
			case 2439: return 78;   // 203Pt
			case 2440: return 78;   // 204Pt
			case 2441: return 78;   // 205Pt
			case 2442: return 78;   // 206Pt
			case 2443: return 79;   // 169Au
			case 2444: return 79;   // 170Au
			case 2445: return 79;   // 171Au
			case 2446: return 79;   // 172Au
			case 2447: return 79;   // 173Au
			case 2448: return 79;   // 174Au
			case 2449: return 79;   // 175Au
			case 2450: return 79;   // 176Au
			case 2451: return 79;   // 177Au
			case 2452: return 79;   // 178Au
			case 2453: return 79;   // 179Au
			case 2454: return 79;   // 180Au
			case 2455: return 79;   // 181Au
			case 2456: return 79;   // 182Au
			case 2457: return 79;   // 183Au
			case 2458: return 79;   // 184Au
			case 2459: return 79;   // 185Au
			case 2460: return 79;   // 186Au
			case 2461: return 79;   // 187Au
			case 2462: return 79;   // 188Au
			case 2463: return 79;   // 189Au
			case 2464: return 79;   // 190Au
			case 2465: return 79;   // 191Au
			case 2466: return 79;   // 192Au
			case 2467: return 79;   // 193Au
			case 2468: return 79;   // 194Au
			case 2469: return 79;   // 195Au
			case 2470: return 79;   // 196Au
			case 2471: return 79;   // 197Au
			case 2472: return 79;   // 198Au
			case 2473: return 79;   // 199Au
			case 2474: return 79;   // 200Au
			case 2475: return 79;   // 201Au
			case 2476: return 79;   // 202Au
			case 2477: return 79;   // 203Au
			case 2478: return 79;   // 204Au
			case 2479: return 79;   // 205Au
			case 2480: return 79;   // 206Au
			case 2481: return 79;   // 207Au
			case 2482: return 79;   // 208Au
			case 2483: return 79;   // 209Au
			case 2484: return 79;   // 210Au
			case 2485: return 80;   // 171Hg
			case 2486: return 80;   // 172Hg
			case 2487: return 80;   // 173Hg
			case 2488: return 80;   // 174Hg
			case 2489: return 80;   // 175Hg
			case 2490: return 80;   // 176Hg
			case 2491: return 80;   // 177Hg
			case 2492: return 80;   // 178Hg
			case 2493: return 80;   // 179Hg
			case 2494: return 80;   // 180Hg
			case 2495: return 80;   // 181Hg
			case 2496: return 80;   // 182Hg
			case 2497: return 80;   // 183Hg
			case 2498: return 80;   // 184Hg
			case 2499: return 80;   // 185Hg
			case 2500: return 80;   // 186Hg
			case 2501: return 80;   // 187Hg
			case 2502: return 80;   // 188Hg
			case 2503: return 80;   // 189Hg
			case 2504: return 80;   // 190Hg
			case 2505: return 80;   // 191Hg
			case 2506: return 80;   // 192Hg
			case 2507: return 80;   // 193Hg
			case 2508: return 80;   // 194Hg
			case 2509: return 80;   // 195Hg
			case 2510: return 80;   // 196Hg
			case 2511: return 80;   // 197Hg
			case 2512: return 80;   // 198Hg
			case 2513: return 80;   // 199Hg
			case 2514: return 80;   // 200Hg
			case 2515: return 80;   // 201Hg
			case 2516: return 80;   // 202Hg
			case 2517: return 80;   // 203Hg
			case 2518: return 80;   // 204Hg
			case 2519: return 80;   // 205Hg
			case 2520: return 80;   // 206Hg
			case 2521: return 80;   // 207Hg
			case 2522: return 80;   // 208Hg
			case 2523: return 80;   // 209Hg
			case 2524: return 80;   // 210Hg
			case 2525: return 80;   // 211Hg
			case 2526: return 80;   // 212Hg
			case 2527: return 80;   // 213Hg
			case 2528: return 80;   // 214Hg
			case 2529: return 80;   // 215Hg
			case 2530: return 80;   // 216Hg
			case 2531: return 81;   // 176Tl
			case 2532: return 81;   // 177Tl
			case 2533: return 81;   // 178Tl
			case 2534: return 81;   // 179Tl
			case 2535: return 81;   // 180Tl
			case 2536: return 81;   // 181Tl
			case 2537: return 81;   // 182Tl
			case 2538: return 81;   // 183Tl
			case 2539: return 81;   // 184Tl
			case 2540: return 81;   // 185Tl
			case 2541: return 81;   // 186Tl
			case 2542: return 81;   // 187Tl
			case 2543: return 81;   // 188Tl
			case 2544: return 81;   // 189Tl
			case 2545: return 81;   // 190Tl
			case 2546: return 81;   // 191Tl
			case 2547: return 81;   // 192Tl
			case 2548: return 81;   // 193Tl
			case 2549: return 81;   // 194Tl
			case 2550: return 81;   // 195Tl
			case 2551: return 81;   // 196Tl
			case 2552: return 81;   // 197Tl
			case 2553: return 81;   // 198Tl
			case 2554: return 81;   // 199Tl
			case 2555: return 81;   // 200Tl
			case 2556: return 81;   // 201Tl
			case 2557: return 81;   // 202Tl
			case 2558: return 81;   // 203Tl
			case 2559: return 81;   // 204Tl
			case 2560: return 81;   // 205Tl
			case 2561: return 81;   // 206Tl
			case 2562: return 81;   // 207Tl
			case 2563: return 81;   // 208Tl
			case 2564: return 81;   // 209Tl
			case 2565: return 81;   // 210Tl
			case 2566: return 81;   // 211Tl
			case 2567: return 81;   // 212Tl
			case 2568: return 81;   // 213Tl
			case 2569: return 81;   // 214Tl
			case 2570: return 81;   // 215Tl
			case 2571: return 81;   // 216Tl
			case 2572: return 81;   // 217Tl
			case 2573: return 81;   // 218Tl
			case 2574: return 82;   // 178Pb
			case 2575: return 82;   // 179Pb
			case 2576: return 82;   // 180Pb
			case 2577: return 82;   // 181Pb
			case 2578: return 82;   // 182Pb
			case 2579: return 82;   // 183Pb
			case 2580: return 82;   // 184Pb
			case 2581: return 82;   // 185Pb
			case 2582: return 82;   // 186Pb
			case 2583: return 82;   // 187Pb
			case 2584: return 82;   // 188Pb
			case 2585: return 82;   // 189Pb
			case 2586: return 82;   // 190Pb
			case 2587: return 82;   // 191Pb
			case 2588: return 82;   // 192Pb
			case 2589: return 82;   // 193Pb
			case 2590: return 82;   // 194Pb
			case 2591: return 82;   // 195Pb
			case 2592: return 82;   // 196Pb
			case 2593: return 82;   // 197Pb
			case 2594: return 82;   // 198Pb
			case 2595: return 82;   // 199Pb
			case 2596: return 82;   // 200Pb
			case 2597: return 82;   // 201Pb
			case 2598: return 82;   // 202Pb
			case 2599: return 82;   // 203Pb
			case 2600: return 82;   // 204Pb
			case 2601: return 82;   // 205Pb
			case 2602: return 82;   // 206Pb
			case 2603: return 82;   // 207Pb
			case 2604: return 82;   // 208Pb
			case 2605: return 82;   // 209Pb
			case 2606: return 82;   // 210Pb
			case 2607: return 82;   // 211Pb
			case 2608: return 82;   // 212Pb
			case 2609: return 82;   // 213Pb
			case 2610: return 82;   // 214Pb
			case 2611: return 82;   // 215Pb
			case 2612: return 82;   // 216Pb
			case 2613: return 82;   // 217Pb
			case 2614: return 82;   // 218Pb
			case 2615: return 82;   // 219Pb
			case 2616: return 82;   // 220Pb
			case 2617: return 83;   // 184Bi
			case 2618: return 83;   // 185Bi
			case 2619: return 83;   // 186Bi
			case 2620: return 83;   // 187Bi
			case 2621: return 83;   // 188Bi
			case 2622: return 83;   // 189Bi
			case 2623: return 83;   // 190Bi
			case 2624: return 83;   // 191Bi
			case 2625: return 83;   // 192Bi
			case 2626: return 83;   // 193Bi
			case 2627: return 83;   // 194Bi
			case 2628: return 83;   // 195Bi
			case 2629: return 83;   // 196Bi
			case 2630: return 83;   // 197Bi
			case 2631: return 83;   // 198Bi
			case 2632: return 83;   // 199Bi
			case 2633: return 83;   // 200Bi
			case 2634: return 83;   // 201Bi
			case 2635: return 83;   // 202Bi
			case 2636: return 83;   // 203Bi
			case 2637: return 83;   // 204Bi
			case 2638: return 83;   // 205Bi
			case 2639: return 83;   // 206Bi
			case 2640: return 83;   // 207Bi
			case 2641: return 83;   // 208Bi
			case 2642: return 83;   // 209Bi
			case 2643: return 83;   // 210Bi
			case 2644: return 83;   // 211Bi
			case 2645: return 83;   // 212Bi
			case 2646: return 83;   // 213Bi
			case 2647: return 83;   // 214Bi
			case 2648: return 83;   // 215Bi
			case 2649: return 83;   // 216Bi
			case 2650: return 83;   // 217Bi
			case 2651: return 83;   // 218Bi
			case 2652: return 83;   // 219Bi
			case 2653: return 83;   // 220Bi
			case 2654: return 83;   // 221Bi
			case 2655: return 83;   // 222Bi
			case 2656: return 83;   // 223Bi
			case 2657: return 83;   // 224Bi
			case 2658: return 84;   // 186Po
			case 2659: return 84;   // 187Po
			case 2660: return 84;   // 188Po
			case 2661: return 84;   // 189Po
			case 2662: return 84;   // 190Po
			case 2663: return 84;   // 191Po
			case 2664: return 84;   // 192Po
			case 2665: return 84;   // 193Po
			case 2666: return 84;   // 194Po
			case 2667: return 84;   // 195Po
			case 2668: return 84;   // 196Po
			case 2669: return 84;   // 197Po
			case 2670: return 84;   // 198Po
			case 2671: return 84;   // 199Po
			case 2672: return 84;   // 200Po
			case 2673: return 84;   // 201Po
			case 2674: return 84;   // 202Po
			case 2675: return 84;   // 203Po
			case 2676: return 84;   // 204Po
			case 2677: return 84;   // 205Po
			case 2678: return 84;   // 206Po
			case 2679: return 84;   // 207Po
			case 2680: return 84;   // 208Po
			case 2681: return 84;   // 209Po
			case 2682: return 84;   // 210Po
			case 2683: return 84;   // 211Po
			case 2684: return 84;   // 212Po
			case 2685: return 84;   // 213Po
			case 2686: return 84;   // 214Po
			case 2687: return 84;   // 215Po
			case 2688: return 84;   // 216Po
			case 2689: return 84;   // 217Po
			case 2690: return 84;   // 218Po
			case 2691: return 84;   // 219Po
			case 2692: return 84;   // 220Po
			case 2693: return 84;   // 221Po
			case 2694: return 84;   // 222Po
			case 2695: return 84;   // 223Po
			case 2696: return 84;   // 224Po
			case 2697: return 84;   // 225Po
			case 2698: return 84;   // 226Po
			case 2699: return 84;   // 227Po
			case 2700: return 85;   // 191At
			case 2701: return 85;   // 192At
			case 2702: return 85;   // 193At
			case 2703: return 85;   // 194At
			case 2704: return 85;   // 195At
			case 2705: return 85;   // 196At
			case 2706: return 85;   // 197At
			case 2707: return 85;   // 198At
			case 2708: return 85;   // 199At
			case 2709: return 85;   // 200At
			case 2710: return 85;   // 201At
			case 2711: return 85;   // 202At
			case 2712: return 85;   // 203At
			case 2713: return 85;   // 204At
			case 2714: return 85;   // 205At
			case 2715: return 85;   // 206At
			case 2716: return 85;   // 207At
			case 2717: return 85;   // 208At
			case 2718: return 85;   // 209At
			case 2719: return 85;   // 210At
			case 2720: return 85;   // 211At
			case 2721: return 85;   // 212At
			case 2722: return 85;   // 213At
			case 2723: return 85;   // 214At
			case 2724: return 85;   // 215At
			case 2725: return 85;   // 216At
			case 2726: return 85;   // 217At
			case 2727: return 85;   // 218At
			case 2728: return 85;   // 219At
			case 2729: return 85;   // 220At
			case 2730: return 85;   // 221At
			case 2731: return 85;   // 222At
			case 2732: return 85;   // 223At
			case 2733: return 85;   // 224At
			case 2734: return 85;   // 225At
			case 2735: return 85;   // 226At
			case 2736: return 85;   // 227At
			case 2737: return 85;   // 228At
			case 2738: return 85;   // 229At
			case 2739: return 86;   // 193Rn
			case 2740: return 86;   // 194Rn
			case 2741: return 86;   // 195Rn
			case 2742: return 86;   // 196Rn
			case 2743: return 86;   // 197Rn
			case 2744: return 86;   // 198Rn
			case 2745: return 86;   // 199Rn
			case 2746: return 86;   // 200Rn
			case 2747: return 86;   // 201Rn
			case 2748: return 86;   // 202Rn
			case 2749: return 86;   // 203Rn
			case 2750: return 86;   // 204Rn
			case 2751: return 86;   // 205Rn
			case 2752: return 86;   // 206Rn
			case 2753: return 86;   // 207Rn
			case 2754: return 86;   // 208Rn
			case 2755: return 86;   // 209Rn
			case 2756: return 86;   // 210Rn
			case 2757: return 86;   // 211Rn
			case 2758: return 86;   // 212Rn
			case 2759: return 86;   // 213Rn
			case 2760: return 86;   // 214Rn
			case 2761: return 86;   // 215Rn
			case 2762: return 86;   // 216Rn
			case 2763: return 86;   // 217Rn
			case 2764: return 86;   // 218Rn
			case 2765: return 86;   // 219Rn
			case 2766: return 86;   // 220Rn
			case 2767: return 86;   // 221Rn
			case 2768: return 86;   // 222Rn
			case 2769: return 86;   // 223Rn
			case 2770: return 86;   // 224Rn
			case 2771: return 86;   // 225Rn
			case 2772: return 86;   // 226Rn
			case 2773: return 86;   // 227Rn
			case 2774: return 86;   // 228Rn
			case 2775: return 86;   // 229Rn
			case 2776: return 86;   // 230Rn
			case 2777: return 86;   // 231Rn
			case 2778: return 87;   // 199Fr
			case 2779: return 87;   // 200Fr
			case 2780: return 87;   // 201Fr
			case 2781: return 87;   // 202Fr
			case 2782: return 87;   // 203Fr
			case 2783: return 87;   // 204Fr
			case 2784: return 87;   // 205Fr
			case 2785: return 87;   // 206Fr
			case 2786: return 87;   // 207Fr
			case 2787: return 87;   // 208Fr
			case 2788: return 87;   // 209Fr
			case 2789: return 87;   // 210Fr
			case 2790: return 87;   // 211Fr
			case 2791: return 87;   // 212Fr
			case 2792: return 87;   // 213Fr
			case 2793: return 87;   // 214Fr
			case 2794: return 87;   // 215Fr
			case 2795: return 87;   // 216Fr
			case 2796: return 87;   // 217Fr
			case 2797: return 87;   // 218Fr
			case 2798: return 87;   // 219Fr
			case 2799: return 87;   // 220Fr
			case 2800: return 87;   // 221Fr
			case 2801: return 87;   // 222Fr
			case 2802: return 87;   // 223Fr
			case 2803: return 87;   // 224Fr
			case 2804: return 87;   // 225Fr
			case 2805: return 87;   // 226Fr
			case 2806: return 87;   // 227Fr
			case 2807: return 87;   // 228Fr
			case 2808: return 87;   // 229Fr
			case 2809: return 87;   // 230Fr
			case 2810: return 87;   // 231Fr
			case 2811: return 87;   // 232Fr
			case 2812: return 87;   // 233Fr
			case 2813: return 88;   // 201Ra
			case 2814: return 88;   // 202Ra
			case 2815: return 88;   // 203Ra
			case 2816: return 88;   // 204Ra
			case 2817: return 88;   // 205Ra
			case 2818: return 88;   // 206Ra
			case 2819: return 88;   // 207Ra
			case 2820: return 88;   // 208Ra
			case 2821: return 88;   // 209Ra
			case 2822: return 88;   // 210Ra
			case 2823: return 88;   // 211Ra
			case 2824: return 88;   // 212Ra
			case 2825: return 88;   // 213Ra
			case 2826: return 88;   // 214Ra
			case 2827: return 88;   // 215Ra
			case 2828: return 88;   // 216Ra
			case 2829: return 88;   // 217Ra
			case 2830: return 88;   // 218Ra
			case 2831: return 88;   // 219Ra
			case 2832: return 88;   // 220Ra
			case 2833: return 88;   // 221Ra
			case 2834: return 88;   // 222Ra
			case 2835: return 88;   // 223Ra
			case 2836: return 88;   // 224Ra
			case 2837: return 88;   // 225Ra
			case 2838: return 88;   // 226Ra
			case 2839: return 88;   // 227Ra
			case 2840: return 88;   // 228Ra
			case 2841: return 88;   // 229Ra
			case 2842: return 88;   // 230Ra
			case 2843: return 88;   // 231Ra
			case 2844: return 88;   // 232Ra
			case 2845: return 88;   // 233Ra
			case 2846: return 88;   // 234Ra
			case 2847: return 88;   // 235Ra
			case 2848: return 89;   // 206Ac
			case 2849: return 89;   // 207Ac
			case 2850: return 89;   // 208Ac
			case 2851: return 89;   // 209Ac
			case 2852: return 89;   // 210Ac
			case 2853: return 89;   // 211Ac
			case 2854: return 89;   // 212Ac
			case 2855: return 89;   // 213Ac
			case 2856: return 89;   // 214Ac
			case 2857: return 89;   // 215Ac
			case 2858: return 89;   // 216Ac
			case 2859: return 89;   // 217Ac
			case 2860: return 89;   // 218Ac
			case 2861: return 89;   // 219Ac
			case 2862: return 89;   // 220Ac
			case 2863: return 89;   // 221Ac
			case 2864: return 89;   // 222Ac
			case 2865: return 89;   // 223Ac
			case 2866: return 89;   // 224Ac
			case 2867: return 89;   // 225Ac
			case 2868: return 89;   // 226Ac
			case 2869: return 89;   // 227Ac
			case 2870: return 89;   // 228Ac
			case 2871: return 89;   // 229Ac
			case 2872: return 89;   // 230Ac
			case 2873: return 89;   // 231Ac
			case 2874: return 89;   // 232Ac
			case 2875: return 89;   // 233Ac
			case 2876: return 89;   // 234Ac
			case 2877: return 89;   // 235Ac
			case 2878: return 89;   // 236Ac
			case 2879: return 89;   // 237Ac
			case 2880: return 90;   // 208Th
			case 2881: return 90;   // 209Th
			case 2882: return 90;   // 210Th
			case 2883: return 90;   // 211Th
			case 2884: return 90;   // 212Th
			case 2885: return 90;   // 213Th
			case 2886: return 90;   // 214Th
			case 2887: return 90;   // 215Th
			case 2888: return 90;   // 216Th
			case 2889: return 90;   // 217Th
			case 2890: return 90;   // 218Th
			case 2891: return 90;   // 219Th
			case 2892: return 90;   // 220Th
			case 2893: return 90;   // 221Th
			case 2894: return 90;   // 222Th
			case 2895: return 90;   // 223Th
			case 2896: return 90;   // 224Th
			case 2897: return 90;   // 225Th
			case 2898: return 90;   // 226Th
			case 2899: return 90;   // 227Th
			case 2900: return 90;   // 228Th
			case 2901: return 90;   // 229Th
			case 2902: return 90;   // 230Th
			case 2903: return 90;   // 231Th
			case 2904: return 90;   // 232Th
			case 2905: return 90;   // 233Th
			case 2906: return 90;   // 234Th
			case 2907: return 90;   // 235Th
			case 2908: return 90;   // 236Th
			case 2909: return 90;   // 237Th
			case 2910: return 90;   // 238Th
			case 2911: return 90;   // 239Th
			case 2912: return 91;   // 212Pa
			case 2913: return 91;   // 213Pa
			case 2914: return 91;   // 214Pa
			case 2915: return 91;   // 215Pa
			case 2916: return 91;   // 216Pa
			case 2917: return 91;   // 217Pa
			case 2918: return 91;   // 218Pa
			case 2919: return 91;   // 219Pa
			case 2920: return 91;   // 220Pa
			case 2921: return 91;   // 221Pa
			case 2922: return 91;   // 222Pa
			case 2923: return 91;   // 223Pa
			case 2924: return 91;   // 224Pa
			case 2925: return 91;   // 225Pa
			case 2926: return 91;   // 226Pa
			case 2927: return 91;   // 227Pa
			case 2928: return 91;   // 228Pa
			case 2929: return 91;   // 229Pa
			case 2930: return 91;   // 230Pa
			case 2931: return 91;   // 231Pa
			case 2932: return 91;   // 232Pa
			case 2933: return 91;   // 233Pa
			case 2934: return 91;   // 234Pa
			case 2935: return 91;   // 235Pa
			case 2936: return 91;   // 236Pa
			case 2937: return 91;   // 237Pa
			case 2938: return 91;   // 238Pa
			case 2939: return 91;   // 239Pa
			case 2940: return 91;   // 240Pa
			case 2941: return 91;   // 241Pa
			case 2942: return 92;   // 217U
			case 2943: return 92;   // 218U
			case 2944: return 92;   // 219U
			case 2945: return 92;   // 220U
			case 2946: return 92;   // 221U
			case 2947: return 92;   // 222U
			case 2948: return 92;   // 223U
			case 2949: return 92;   // 224U
			case 2950: return 92;   // 225U
			case 2951: return 92;   // 226U
			case 2952: return 92;   // 227U
			case 2953: return 92;   // 228U
			case 2954: return 92;   // 229U
			case 2955: return 92;   // 230U
			case 2956: return 92;   // 231U
			case 2957: return 92;   // 232U
			case 2958: return 92;   // 233U
			case 2959: return 92;   // 234U
			case 2960: return 92;   // 235U
			case 2961: return 92;   // 236U
			case 2962: return 92;   // 237U
			case 2963: return 92;   // 238U
			case 2964: return 92;   // 239U
			case 2965: return 92;   // 240U
			case 2966: return 92;   // 241U
			case 2967: return 92;   // 242U
			case 2968: return 92;   // 243U
			case 2969: return 93;   // 219Np
			case 2970: return 93;   // 220Np
			case 2971: return 93;   // 221Np
			case 2972: return 93;   // 222Np
			case 2973: return 93;   // 223Np
			case 2974: return 93;   // 224Np
			case 2975: return 93;   // 225Np
			case 2976: return 93;   // 226Np
			case 2977: return 93;   // 227Np
			case 2978: return 93;   // 228Np
			case 2979: return 93;   // 229Np
			case 2980: return 93;   // 230Np
			case 2981: return 93;   // 231Np
			case 2982: return 93;   // 232Np
			case 2983: return 93;   // 233Np
			case 2984: return 93;   // 234Np
			case 2985: return 93;   // 235Np
			case 2986: return 93;   // 236Np
			case 2987: return 93;   // 237Np
			case 2988: return 93;   // 238Np
			case 2989: return 93;   // 239Np
			case 2990: return 93;   // 240Np
			case 2991: return 93;   // 241Np
			case 2992: return 93;   // 242Np
			case 2993: return 93;   // 243Np
			case 2994: return 93;   // 244Np
			case 2995: return 93;   // 245Np
			case 2996: return 94;   // 228Pu
			case 2997: return 94;   // 229Pu
			case 2998: return 94;   // 230Pu
			case 2999: return 94;   // 231Pu
			case 3000: return 94;   // 232Pu
			case 3001: return 94;   // 233Pu
			case 3002: return 94;   // 234Pu
			case 3003: return 94;   // 235Pu
			case 3004: return 94;   // 236Pu
			case 3005: return 94;   // 237Pu
			case 3006: return 94;   // 238Pu
			case 3007: return 94;   // 239Pu
			case 3008: return 94;   // 240Pu
			case 3009: return 94;   // 241Pu
			case 3010: return 94;   // 242Pu
			case 3011: return 94;   // 243Pu
			case 3012: return 94;   // 244Pu
			case 3013: return 94;   // 245Pu
			case 3014: return 94;   // 246Pu
			case 3015: return 94;   // 247Pu
			case 3016: return 95;   // 230Am
			case 3017: return 95;   // 231Am
			case 3018: return 95;   // 232Am
			case 3019: return 95;   // 233Am
			case 3020: return 95;   // 234Am
			case 3021: return 95;   // 235Am
			case 3022: return 95;   // 236Am
			case 3023: return 95;   // 237Am
			case 3024: return 95;   // 238Am
			case 3025: return 95;   // 239Am
			case 3026: return 95;   // 240Am
			case 3027: return 95;   // 241Am
			case 3028: return 95;   // 242Am
			case 3029: return 95;   // 243Am
			case 3030: return 95;   // 244Am
			case 3031: return 95;   // 245Am
			case 3032: return 95;   // 246Am
			case 3033: return 95;   // 247Am
			case 3034: return 95;   // 248Am
			case 3035: return 95;   // 249Am
			case 3036: return 96;   // 232Cm
			case 3037: return 96;   // 233Cm
			case 3038: return 96;   // 234Cm
			case 3039: return 96;   // 235Cm
			case 3040: return 96;   // 236Cm
			case 3041: return 96;   // 237Cm
			case 3042: return 96;   // 238Cm
			case 3043: return 96;   // 239Cm
			case 3044: return 96;   // 240Cm
			case 3045: return 96;   // 241Cm
			case 3046: return 96;   // 242Cm
			case 3047: return 96;   // 243Cm
			case 3048: return 96;   // 244Cm
			case 3049: return 96;   // 245Cm
			case 3050: return 96;   // 246Cm
			case 3051: return 96;   // 247Cm
			case 3052: return 96;   // 248Cm
			case 3053: return 96;   // 249Cm
			case 3054: return 96;   // 250Cm
			case 3055: return 96;   // 251Cm
			case 3056: return 96;   // 252Cm
			case 3057: return 97;   // 234Bk
			case 3058: return 97;   // 235Bk
			case 3059: return 97;   // 236Bk
			case 3060: return 97;   // 237Bk
			case 3061: return 97;   // 238Bk
			case 3062: return 97;   // 239Bk
			case 3063: return 97;   // 240Bk
			case 3064: return 97;   // 241Bk
			case 3065: return 97;   // 242Bk
			case 3066: return 97;   // 243Bk
			case 3067: return 97;   // 244Bk
			case 3068: return 97;   // 245Bk
			case 3069: return 97;   // 246Bk
			case 3070: return 97;   // 247Bk
			case 3071: return 97;   // 248Bk
			case 3072: return 97;   // 249Bk
			case 3073: return 97;   // 250Bk
			case 3074: return 97;   // 251Bk
			case 3075: return 97;   // 252Bk
			case 3076: return 97;   // 253Bk
			case 3077: return 97;   // 254Bk
			case 3078: return 98;   // 237Cf
			case 3079: return 98;   // 238Cf
			case 3080: return 98;   // 239Cf
			case 3081: return 98;   // 240Cf
			case 3082: return 98;   // 241Cf
			case 3083: return 98;   // 242Cf
			case 3084: return 98;   // 243Cf
			case 3085: return 98;   // 244Cf
			case 3086: return 98;   // 245Cf
			case 3087: return 98;   // 246Cf
			case 3088: return 98;   // 247Cf
			case 3089: return 98;   // 248Cf
			case 3090: return 98;   // 249Cf
			case 3091: return 98;   // 250Cf
			case 3092: return 98;   // 251Cf
			case 3093: return 98;   // 252Cf
			case 3094: return 98;   // 253Cf
			case 3095: return 98;   // 254Cf
			case 3096: return 98;   // 255Cf
			case 3097: return 98;   // 256Cf
			case 3098: return 99;   // 239Es
			case 3099: return 99;   // 240Es
			case 3100: return 99;   // 241Es
			case 3101: return 99;   // 242Es
			case 3102: return 99;   // 243Es
			case 3103: return 99;   // 244Es
			case 3104: return 99;   // 245Es
			case 3105: return 99;   // 246Es
			case 3106: return 99;   // 247Es
			case 3107: return 99;   // 248Es
			case 3108: return 99;   // 249Es
			case 3109: return 99;   // 250Es
			case 3110: return 99;   // 251Es
			case 3111: return 99;   // 252Es
			case 3112: return 99;   // 253Es
			case 3113: return 99;   // 254Es
			case 3114: return 99;   // 255Es
			case 3115: return 99;   // 256Es
			case 3116: return 99;   // 257Es
			case 3117: return 99;   // 258Es
			case 3118: return 100;  // 241Fm
			case 3119: return 100;  // 242Fm
			case 3120: return 100;  // 243Fm
			case 3121: return 100;  // 244Fm
			case 3122: return 100;  // 245Fm
			case 3123: return 100;  // 246Fm
			case 3124: return 100;  // 247Fm
			case 3125: return 100;  // 248Fm
			case 3126: return 100;  // 249Fm
			case 3127: return 100;  // 250Fm
			case 3128: return 100;  // 251Fm
			case 3129: return 100;  // 252Fm
			case 3130: return 100;  // 253Fm
			case 3131: return 100;  // 254Fm
			case 3132: return 100;  // 255Fm
			case 3133: return 100;  // 256Fm
			case 3134: return 100;  // 257Fm
			case 3135: return 100;  // 258Fm
			case 3136: return 100;  // 259Fm
			case 3137: return 100;  // 260Fm
			case 3138: return 101;  // 245Md
			case 3139: return 101;  // 246Md
			case 3140: return 101;  // 247Md
			case 3141: return 101;  // 248Md
			case 3142: return 101;  // 249Md
			case 3143: return 101;  // 250Md
			case 3144: return 101;  // 251Md
			case 3145: return 101;  // 252Md
			case 3146: return 101;  // 253Md
			case 3147: return 101;  // 254Md
			case 3148: return 101;  // 255Md
			case 3149: return 101;  // 256Md
			case 3150: return 101;  // 257Md
			case 3151: return 101;  // 258Md
			case 3152: return 101;  // 259Md
			case 3153: return 101;  // 260Md
			case 3154: return 101;  // 261Md
			case 3155: return 101;  // 262Md
			case 3156: return 102;  // 248No
			case 3157: return 102;  // 249No
			case 3158: return 102;  // 250No
			case 3159: return 102;  // 251No
			case 3160: return 102;  // 252No
			case 3161: return 102;  // 253No
			case 3162: return 102;  // 254No
			case 3163: return 102;  // 255No
			case 3164: return 102;  // 256No
			case 3165: return 102;  // 257No
			case 3166: return 102;  // 258No
			case 3167: return 102;  // 259No
			case 3168: return 102;  // 260No
			case 3169: return 102;  // 261No
			case 3170: return 102;  // 262No
			case 3171: return 102;  // 263No
			case 3172: return 102;  // 264No
			case 3173: return 103;  // 251Lr
			case 3174: return 103;  // 252Lr
			case 3175: return 103;  // 253Lr
			case 3176: return 103;  // 254Lr
			case 3177: return 103;  // 255Lr
			case 3178: return 103;  // 256Lr
			case 3179: return 103;  // 257Lr
			case 3180: return 103;  // 258Lr
			case 3181: return 103;  // 259Lr
			case 3182: return 103;  // 260Lr
			case 3183: return 103;  // 261Lr
			case 3184: return 103;  // 262Lr
			case 3185: return 103;  // 263Lr
			case 3186: return 103;  // 264Lr
			case 3187: return 103;  // 265Lr
			case 3188: return 103;  // 266Lr
			case 3189: return 104;  // 253Rf
			case 3190: return 104;  // 254Rf
			case 3191: return 104;  // 255Rf
			case 3192: return 104;  // 256Rf
			case 3193: return 104;  // 257Rf
			case 3194: return 104;  // 258Rf
			case 3195: return 104;  // 259Rf
			case 3196: return 104;  // 260Rf
			case 3197: return 104;  // 261Rf
			case 3198: return 104;  // 262Rf
			case 3199: return 104;  // 263Rf
			case 3200: return 104;  // 264Rf
			case 3201: return 104;  // 265Rf
			case 3202: return 104;  // 266Rf
			case 3203: return 104;  // 267Rf
			case 3204: return 104;  // 268Rf
			case 3205: return 105;  // 255Db
			case 3206: return 105;  // 256Db
			case 3207: return 105;  // 257Db
			case 3208: return 105;  // 258Db
			case 3209: return 105;  // 259Db
			case 3210: return 105;  // 260Db
			case 3211: return 105;  // 261Db
			case 3212: return 105;  // 262Db
			case 3213: return 105;  // 263Db
			case 3214: return 105;  // 264Db
			case 3215: return 105;  // 265Db
			case 3216: return 105;  // 266Db
			case 3217: return 105;  // 267Db
			case 3218: return 105;  // 268Db
			case 3219: return 105;  // 269Db
			case 3220: return 105;  // 270Db
			case 3221: return 106;  // 258Sg
			case 3222: return 106;  // 259Sg
			case 3223: return 106;  // 260Sg
			case 3224: return 106;  // 261Sg
			case 3225: return 106;  // 262Sg
			case 3226: return 106;  // 263Sg
			case 3227: return 106;  // 264Sg
			case 3228: return 106;  // 265Sg
			case 3229: return 106;  // 266Sg
			case 3230: return 106;  // 267Sg
			case 3231: return 106;  // 268Sg
			case 3232: return 106;  // 269Sg
			case 3233: return 106;  // 270Sg
			case 3234: return 106;  // 271Sg
			case 3235: return 106;  // 272Sg
			case 3236: return 106;  // 273Sg
			case 3237: return 107;  // 260Bh
			case 3238: return 107;  // 261Bh
			case 3239: return 107;  // 262Bh
			case 3240: return 107;  // 263Bh
			case 3241: return 107;  // 264Bh
			case 3242: return 107;  // 265Bh
			case 3243: return 107;  // 266Bh
			case 3244: return 107;  // 267Bh
			case 3245: return 107;  // 268Bh
			case 3246: return 107;  // 269Bh
			case 3247: return 107;  // 270Bh
			case 3248: return 107;  // 271Bh
			case 3249: return 107;  // 272Bh
			case 3250: return 107;  // 273Bh
			case 3251: return 107;  // 274Bh
			case 3252: return 107;  // 275Bh
			case 3253: return 108;  // 263Hs
			case 3254: return 108;  // 264Hs
			case 3255: return 108;  // 265Hs
			case 3256: return 108;  // 266Hs
			case 3257: return 108;  // 267Hs
			case 3258: return 108;  // 268Hs
			case 3259: return 108;  // 269Hs
			case 3260: return 108;  // 270Hs
			case 3261: return 108;  // 271Hs
			case 3262: return 108;  // 272Hs
			case 3263: return 108;  // 273Hs
			case 3264: return 108;  // 274Hs
			case 3265: return 108;  // 275Hs
			case 3266: return 108;  // 276Hs
			case 3267: return 108;  // 277Hs
			case 3268: return 109;  // 265Mt
			case 3269: return 109;  // 266Mt
			case 3270: return 109;  // 267Mt
			case 3271: return 109;  // 268Mt
			case 3272: return 109;  // 269Mt
			case 3273: return 109;  // 270Mt
			case 3274: return 109;  // 271Mt
			case 3275: return 109;  // 272Mt
			case 3276: return 109;  // 273Mt
			case 3277: return 109;  // 274Mt
			case 3278: return 109;  // 275Mt
			case 3279: return 109;  // 276Mt
			case 3280: return 109;  // 277Mt
			case 3281: return 109;  // 278Mt
			case 3282: return 109;  // 279Mt
			case 3283: return 110;  // 267Ds
			case 3284: return 110;  // 268Ds
			case 3285: return 110;  // 269Ds
			case 3286: return 110;  // 270Ds
			case 3287: return 110;  // 271Ds
			case 3288: return 110;  // 272Ds
			case 3289: return 110;  // 273Ds
			case 3290: return 110;  // 274Ds
			case 3291: return 110;  // 275Ds
			case 3292: return 110;  // 276Ds
			case 3293: return 110;  // 277Ds
			case 3294: return 110;  // 278Ds
			case 3295: return 110;  // 279Ds
			case 3296: return 110;  // 280Ds
			case 3297: return 110;  // 281Ds
			case 3298: return 111;  // 272Rg
			case 3299: return 111;  // 273Rg
			case 3300: return 111;  // 274Rg
			case 3301: return 111;  // 275Rg
			case 3302: return 111;  // 276Rg
			case 3303: return 111;  // 277Rg
			case 3304: return 111;  // 278Rg
			case 3305: return 111;  // 279Rg
			case 3306: return 111;  // 280Rg
			case 3307: return 111;  // 281Rg
			case 3308: return 111;  // 282Rg
			case 3309: return 111;  // 283Rg
			case 3310: return 112;  // 276Cn
			case 3311: return 112;  // 277Cn
			case 3312: return 112;  // 278Cn
			case 3313: return 112;  // 279Cn
			case 3314: return 112;  // 280Cn
			case 3315: return 112;  // 281Cn
			case 3316: return 112;  // 282Cn
			case 3317: return 112;  // 283Cn
			case 3318: return 112;  // 284Cn
			case 3319: return 112;  // 285Cn
			case 3320: return 113;  // 278Nh
			case 3321: return 113;  // 279Nh
			case 3322: return 113;  // 280Nh
			case 3323: return 113;  // 281Nh
			case 3324: return 113;  // 282Nh
			case 3325: return 113;  // 283Nh
			case 3326: return 113;  // 284Nh
			case 3327: return 113;  // 285Nh
			case 3328: return 113;  // 286Nh
			case 3329: return 113;  // 287Nh
			case 3330: return 114;  // 285Fl
			case 3331: return 114;  // 286Fl
			case 3332: return 114;  // 287Fl
			case 3333: return 114;  // 288Fl
			case 3334: return 114;  // 289Fl
			case 3335: return 115;  // 287Mc
			case 3336: return 115;  // 288Mc
			case 3337: return 115;  // 289Mc
			case 3338: return 115;  // 290Mc
			case 3339: return 115;  // 291Uup
			case 3340: return 116;  // 289Lv
			case 3341: return 116;  // 290Lv
			case 3342: return 116;  // 291Lv
			case 3343: return 116;  // 292Lv
			case 3344: return 116;  // 293Lv
			case 3345: return 117;  // 291Ts
			case 3346: return 117;  // 292Ts
			case 3347: return 117;  // 293Ts
			case 3348: return 117;  // 294Uus
			case 3349: return 118;  // 293Og
			case 3350: return 118;  // 294Og
			case 3351: return 118;  // 295Og
			  default: return 0;
		}
	}

	static constexpr f64 nuclear_spin(const nist::Isotope a)
	{
		// NOTE: The nuclear spin quantum numbers are not from a NIST database,
		// but this was the most convenient place for this data. This was taken
		// from https://easyspin.org/easyspin/documentation/isotopetable.html
		//
		// Below we reproduce relevant comments as found in the original source.
		//
		// Nuclear magnetic moments are taken from
		//   N.Stone
		//   Table of Nuclear Magnetic Dipole and Electric Quadrupole Moments
		//   International Atomic Energy Agency, INDC(NDS)-0658, February 2014
		//     (https://www-nds.iaea.org/publications/indc/indc-nds-0658.pdf)
		//   (Typo for Rh103: Moment is factor of 10 too large)
		//
		//  237Np, 239Pu, 243Am data from
		//   N.E.Holden
		//   Table of the Isotopes
		//   CRC Handbook of Physics and Chemistry, section 11-2
		//     (http://www.hbcponline.com//articles/11_02_92.pdf)
		//
		// Nuclear quadrupole moments are taken from
		//   N.Stone
		//   Table of Nuclear Quadrupole Moments
		//   International Atomic Energy Agency, INDC(NDS)-650, December 2013
		//     (https://www-nds.iaea.org/publications/indc/indc-nds-0650.pdf)
		//  (Typo for Ac227: Sign should be +)
		//
		// See also
		//   P.Pyykkö
		//   Year-2008 Nuclear Quadrupole Moments
		//   Mol.Phys. 106(16-18), 1965-1974 (2008)
		//     (https://doi.org/10.1080/00268970802018367)
		//
		//   N.E.Holden
		//   Table of the Isotopes
		//   CRC Handbook of Physics and Chemistry, section 11-2
		//     (http://www.hbcponline.com//articles/11_02_92.pdf)

		switch (a) {
			case nist::Isotope::atom_1H:    return 0.5;
			case nist::Isotope::atom_2H:    return 1.0;
			case nist::Isotope::atom_3H:    return 0.5;
			case nist::Isotope::atom_3He:   return 0.5;
			case nist::Isotope::atom_4He:   return 0.0;
			case nist::Isotope::atom_6Li:   return 1.0;
			case nist::Isotope::atom_7Li:   return 1.5;
			case nist::Isotope::atom_9Be:   return 1.5;
			case nist::Isotope::atom_10B:   return 3.0;
			case nist::Isotope::atom_11B:   return 1.5;
			case nist::Isotope::atom_12C:   return 0.0;
			case nist::Isotope::atom_13C:   return 0.5;
			case nist::Isotope::atom_14C:   return 0.0;
			case nist::Isotope::atom_14N:   return 1.0;
			case nist::Isotope::atom_15N:   return 0.5;
			case nist::Isotope::atom_16O:   return 0.0;
			case nist::Isotope::atom_17O:   return 2.5;
			case nist::Isotope::atom_18O:   return 0.0;
			case nist::Isotope::atom_19F:   return 0.5;
			case nist::Isotope::atom_20Ne:  return 0.0;
			case nist::Isotope::atom_21Ne:  return 1.5;
			case nist::Isotope::atom_22Ne:  return 0.0;
			case nist::Isotope::atom_22Na:  return 3.0;
			case nist::Isotope::atom_23Na:  return 1.5;
			case nist::Isotope::atom_24Mg:  return 0.0;
			case nist::Isotope::atom_25Mg:  return 2.5;
			case nist::Isotope::atom_26Mg:  return 0.0;
			case nist::Isotope::atom_27Al:  return 2.5;
			case nist::Isotope::atom_28Si:  return 0.0;
			case nist::Isotope::atom_29Si:  return 0.5;
			case nist::Isotope::atom_30Si:  return 0.0;
			case nist::Isotope::atom_31P:   return 0.5;
			case nist::Isotope::atom_32S:   return 0.0;
			case nist::Isotope::atom_33S:   return 1.5;
			case nist::Isotope::atom_34S:   return 0.0;
			case nist::Isotope::atom_36S:   return 0.0;
			case nist::Isotope::atom_35Cl:  return 1.5;
			case nist::Isotope::atom_36Cl:  return 2.0;
			case nist::Isotope::atom_37Cl:  return 1.5;
			case nist::Isotope::atom_36Ar:  return 0.0;
			case nist::Isotope::atom_38Ar:  return 0.0;
			case nist::Isotope::atom_39Ar:  return 3.5;
			case nist::Isotope::atom_40Ar:  return 0.0;
			case nist::Isotope::atom_39K:   return 1.5;
			case nist::Isotope::atom_40K:   return 4.0;
			case nist::Isotope::atom_41K:   return 1.5;
			case nist::Isotope::atom_40Ca:  return 0.0;
			case nist::Isotope::atom_41Ca:  return 3.5;
			case nist::Isotope::atom_42Ca:  return 0.0;
			case nist::Isotope::atom_43Ca:  return 3.5;
			case nist::Isotope::atom_44Ca:  return 0.0;
			case nist::Isotope::atom_46Ca:  return 0.0;
			case nist::Isotope::atom_48Ca:  return 0.0;
			case nist::Isotope::atom_45Sc:  return 3.5;
			case nist::Isotope::atom_46Ti:  return 0.0;
			case nist::Isotope::atom_47Ti:  return 2.5;
			case nist::Isotope::atom_48Ti:  return 0.0;
			case nist::Isotope::atom_49Ti:  return 3.5;
			case nist::Isotope::atom_50Ti:  return 0.0;
			case nist::Isotope::atom_50V:   return 6.0;
			case nist::Isotope::atom_51V:   return 3.5;
			case nist::Isotope::atom_50Cr:  return 0.0;
			case nist::Isotope::atom_52Cr:  return 0.0;
			case nist::Isotope::atom_53Cr:  return 1.5;
			case nist::Isotope::atom_54Cr:  return 0.0;
			case nist::Isotope::atom_53Mn:  return 3.5;
			case nist::Isotope::atom_55Mn:  return 2.5;
			case nist::Isotope::atom_54Fe:  return 0.0;
			case nist::Isotope::atom_56Fe:  return 0.0;
			case nist::Isotope::atom_57Fe:  return 0.5;
			case nist::Isotope::atom_58Fe:  return 0.0;
			case nist::Isotope::atom_59Co:  return 3.5;
			case nist::Isotope::atom_60Co:  return 5.0;
			case nist::Isotope::atom_58Ni:  return 0.0;
			case nist::Isotope::atom_60Ni:  return 0.0;
			case nist::Isotope::atom_61Ni:  return 1.5;
			case nist::Isotope::atom_62Ni:  return 0.0;
			case nist::Isotope::atom_64Ni:  return 0.0;
			case nist::Isotope::atom_63Cu:  return 1.5;
			case nist::Isotope::atom_65Cu:  return 1.5;
			case nist::Isotope::atom_64Zn:  return 0.0;
			case nist::Isotope::atom_66Zn:  return 0.0;
			case nist::Isotope::atom_67Zn:  return 2.5;
			case nist::Isotope::atom_68Zn:  return 0.0;
			case nist::Isotope::atom_70Zn:  return 0.0;
			case nist::Isotope::atom_69Ga:  return 1.5;
			case nist::Isotope::atom_71Ga:  return 1.5;
			case nist::Isotope::atom_70Ge:  return 0.0;
			case nist::Isotope::atom_72Ge:  return 0.0;
			case nist::Isotope::atom_73Ge:  return 4.5;
			case nist::Isotope::atom_74Ge:  return 0.0;
			case nist::Isotope::atom_76Ge:  return 0.0;
			case nist::Isotope::atom_75As:  return 1.5;
			case nist::Isotope::atom_74Se:  return 0.0;
			case nist::Isotope::atom_76Se:  return 0.0;
			case nist::Isotope::atom_77Se:  return 0.5;
			case nist::Isotope::atom_78Se:  return 0.0;
			case nist::Isotope::atom_79Se:  return 3.5;
			case nist::Isotope::atom_80Se:  return 0.0;
			case nist::Isotope::atom_82Se:  return 0.0;
			case nist::Isotope::atom_79Br:  return 1.5;
			case nist::Isotope::atom_81Br:  return 1.5;
			case nist::Isotope::atom_78Kr:  return 0.0;
			case nist::Isotope::atom_80Kr:  return 0.0;
			case nist::Isotope::atom_82Kr:  return 0.0;
			case nist::Isotope::atom_83Kr:  return 4.5;
			case nist::Isotope::atom_84Kr:  return 0.0;
			case nist::Isotope::atom_85Kr:  return 4.5;
			case nist::Isotope::atom_86Kr:  return 0.0;
			case nist::Isotope::atom_85Rb:  return 2.5;
			case nist::Isotope::atom_87Rb:  return 1.5;
			case nist::Isotope::atom_84Sr:  return 0.0;
			case nist::Isotope::atom_86Sr:  return 0.0;
			case nist::Isotope::atom_87Sr:  return 4.5;
			case nist::Isotope::atom_88Sr:  return 0.0;
			case nist::Isotope::atom_89Y:   return 0.5;
			case nist::Isotope::atom_90Zr:  return 0.0;
			case nist::Isotope::atom_91Zr:  return 2.5;
			case nist::Isotope::atom_92Zr:  return 0.0;
			case nist::Isotope::atom_94Zr:  return 0.0;
			case nist::Isotope::atom_96Zr:  return 0.0;
			case nist::Isotope::atom_93Nb:  return 4.5;
			case nist::Isotope::atom_92Mo:  return 0.0;
			case nist::Isotope::atom_94Mo:  return 0.0;
			case nist::Isotope::atom_95Mo:  return 2.5;
			case nist::Isotope::atom_96Mo:  return 0.0;
			case nist::Isotope::atom_97Mo:  return 2.5;
			case nist::Isotope::atom_98Mo:  return 0.0;
			case nist::Isotope::atom_100Mo: return 0.0;
			case nist::Isotope::atom_99Tc:  return 4.5;
			case nist::Isotope::atom_96Ru:  return 0.0;
			case nist::Isotope::atom_98Ru:  return 0.0;
			case nist::Isotope::atom_99Ru:  return 2.5;
			case nist::Isotope::atom_100Ru: return 0.0;
			case nist::Isotope::atom_101Ru: return 2.5;
			case nist::Isotope::atom_102Ru: return 0.0;
			case nist::Isotope::atom_104Ru: return 0.0;
			case nist::Isotope::atom_103Rh: return 0.5;
			case nist::Isotope::atom_102Pd: return 0.0;
			case nist::Isotope::atom_104Pd: return 0.0;
			case nist::Isotope::atom_105Pd: return 2.5;
			case nist::Isotope::atom_106Pd: return 0.0;
			case nist::Isotope::atom_108Pd: return 0.0;
			case nist::Isotope::atom_110Pd: return 0.0;
			case nist::Isotope::atom_107Ag: return 0.5;
			case nist::Isotope::atom_109Ag: return 0.5;
			case nist::Isotope::atom_106Cd: return 0.0;
			case nist::Isotope::atom_108Cd: return 0.0;
			case nist::Isotope::atom_110Cd: return 0.0;
			case nist::Isotope::atom_111Cd: return 0.5;
			case nist::Isotope::atom_112Cd: return 0.0;
			case nist::Isotope::atom_113Cd: return 0.5;
			case nist::Isotope::atom_114Cd: return 0.0;
			case nist::Isotope::atom_116Cd: return 0.0;
			case nist::Isotope::atom_113In: return 4.5;
			case nist::Isotope::atom_115In: return 4.5;
			case nist::Isotope::atom_112Sn: return 0.0;
			case nist::Isotope::atom_114Sn: return 0.0;
			case nist::Isotope::atom_115Sn: return 0.5;
			case nist::Isotope::atom_116Sn: return 0.0;
			case nist::Isotope::atom_117Sn: return 0.5;
			case nist::Isotope::atom_118Sn: return 0.0;
			case nist::Isotope::atom_119Sn: return 0.5;
			case nist::Isotope::atom_120Sn: return 0.0;
			case nist::Isotope::atom_122Sn: return 0.0;
			case nist::Isotope::atom_124Sn: return 0.0;
			case nist::Isotope::atom_121Sb: return 2.5;
			case nist::Isotope::atom_123Sb: return 3.5;
			case nist::Isotope::atom_125Sb: return 3.5;
			case nist::Isotope::atom_120Te: return 0.0;
			case nist::Isotope::atom_122Te: return 0.0;
			case nist::Isotope::atom_123Te: return 0.5;
			case nist::Isotope::atom_124Te: return 0.0;
			case nist::Isotope::atom_125Te: return 0.5;
			case nist::Isotope::atom_126Te: return 0.0;
			case nist::Isotope::atom_128Te: return 0.0;
			case nist::Isotope::atom_130Te: return 0.0;
			case nist::Isotope::atom_127I:  return 2.5;
			case nist::Isotope::atom_129I:  return 3.5;
			case nist::Isotope::atom_124Xe: return 0.0;
			case nist::Isotope::atom_126Xe: return 0.0;
			case nist::Isotope::atom_128Xe: return 0.0;
			case nist::Isotope::atom_129Xe: return 0.5;
			case nist::Isotope::atom_130Xe: return 0.0;
			case nist::Isotope::atom_131Xe: return 1.5;
			case nist::Isotope::atom_132Xe: return 0.0;
			case nist::Isotope::atom_134Xe: return 0.0;
			case nist::Isotope::atom_136Xe: return 0.0;
			case nist::Isotope::atom_133Cs: return 3.5;
			case nist::Isotope::atom_134Cs: return 4.0;
			case nist::Isotope::atom_135Cs: return 3.5;
			case nist::Isotope::atom_137Cs: return 3.5;
			case nist::Isotope::atom_130Ba: return 0.0;
			case nist::Isotope::atom_132Ba: return 0.0;
			case nist::Isotope::atom_133Ba: return 0.5;
			case nist::Isotope::atom_134Ba: return 0.0;
			case nist::Isotope::atom_135Ba: return 1.5;
			case nist::Isotope::atom_136Ba: return 0.0;
			case nist::Isotope::atom_137Ba: return 1.5;
			case nist::Isotope::atom_138Ba: return 0.0;
			case nist::Isotope::atom_137La: return 3.5;
			case nist::Isotope::atom_138La: return 5.0;
			case nist::Isotope::atom_139La: return 3.5;
			case nist::Isotope::atom_136Ce: return 0.0;
			case nist::Isotope::atom_138Ce: return 0.0;
			case nist::Isotope::atom_140Ce: return 0.0;
			case nist::Isotope::atom_142Ce: return 0.0;
			case nist::Isotope::atom_141Pr: return 2.5;
			case nist::Isotope::atom_142Nd: return 0.0;
			case nist::Isotope::atom_143Nd: return 3.5;
			case nist::Isotope::atom_144Nd: return 0.0;
			case nist::Isotope::atom_145Nd: return 3.5;
			case nist::Isotope::atom_146Nd: return 0.0;
			case nist::Isotope::atom_148Nd: return 0.0;
			case nist::Isotope::atom_150Nd: return 0.0;
			case nist::Isotope::atom_147Pm: return 3.5;
			case nist::Isotope::atom_144Sm: return 0.0;
			case nist::Isotope::atom_147Sm: return 3.5;
			case nist::Isotope::atom_148Sm: return 0.0;
			case nist::Isotope::atom_149Sm: return 3.5;
			case nist::Isotope::atom_150Sm: return 0.0;
			case nist::Isotope::atom_151Sm: return 2.5;
			case nist::Isotope::atom_152Sm: return 0.0;
			case nist::Isotope::atom_154Sm: return 0.0;
			case nist::Isotope::atom_151Eu: return 2.5;
			case nist::Isotope::atom_152Eu: return 3.0;
			case nist::Isotope::atom_153Eu: return 2.5;
			case nist::Isotope::atom_154Eu: return 3.0;
			case nist::Isotope::atom_155Eu: return 2.5;
			case nist::Isotope::atom_152Gd: return 0.0;
			case nist::Isotope::atom_154Gd: return 0.0;
			case nist::Isotope::atom_155Gd: return 1.5;
			case nist::Isotope::atom_156Gd: return 0.0;
			case nist::Isotope::atom_157Gd: return 1.5;
			case nist::Isotope::atom_158Gd: return 0.0;
			case nist::Isotope::atom_160Gd: return 0.0;
			case nist::Isotope::atom_157Tb: return 1.5;
			case nist::Isotope::atom_159Tb: return 1.5;
			case nist::Isotope::atom_160Tb: return 3.0;
			case nist::Isotope::atom_156Dy: return 0.0;
			case nist::Isotope::atom_158Dy: return 0.0;
			case nist::Isotope::atom_160Dy: return 0.0;
			case nist::Isotope::atom_161Dy: return 2.5;
			case nist::Isotope::atom_162Dy: return 0.0;
			case nist::Isotope::atom_163Dy: return 2.5;
			case nist::Isotope::atom_164Dy: return 0.0;
			case nist::Isotope::atom_165Ho: return 3.5;
			case nist::Isotope::atom_162Er: return 0.0;
			case nist::Isotope::atom_164Er: return 0.0;
			case nist::Isotope::atom_166Er: return 0.0;
			case nist::Isotope::atom_167Er: return 3.5;
			case nist::Isotope::atom_168Er: return 0.0;
			case nist::Isotope::atom_170Er: return 0.0;
			case nist::Isotope::atom_169Tm: return 0.5;
			case nist::Isotope::atom_171Tm: return 0.5;
			case nist::Isotope::atom_168Yb: return 0.0;
			case nist::Isotope::atom_170Yb: return 0.0;
			case nist::Isotope::atom_171Yb: return 0.5;
			case nist::Isotope::atom_172Yb: return 0.0;
			case nist::Isotope::atom_173Yb: return 2.5;
			case nist::Isotope::atom_174Yb: return 0.0;
			case nist::Isotope::atom_176Yb: return 0.0;
			case nist::Isotope::atom_173Lu: return 3.5;
			case nist::Isotope::atom_174Lu: return 1.0;
			case nist::Isotope::atom_175Lu: return 3.5;
			case nist::Isotope::atom_176Lu: return 7.0;
			case nist::Isotope::atom_174Hf: return 0.0;
			case nist::Isotope::atom_176Hf: return 0.0;
			case nist::Isotope::atom_177Hf: return 3.5;
			case nist::Isotope::atom_178Hf: return 0.0;
			case nist::Isotope::atom_179Hf: return 4.5;
			case nist::Isotope::atom_180Hf: return 0.0;
			case nist::Isotope::atom_180Ta: return 9.0;
			case nist::Isotope::atom_181Ta: return 3.5;
			case nist::Isotope::atom_180W:  return 0.0;
			case nist::Isotope::atom_182W:  return 0.0;
			case nist::Isotope::atom_183W:  return 0.5;
			case nist::Isotope::atom_184W:  return 0.0;
			case nist::Isotope::atom_186W:  return 0.0;
			case nist::Isotope::atom_185Re: return 2.5;
			case nist::Isotope::atom_187Re: return 2.5;
			case nist::Isotope::atom_184Os: return 0.0;
			case nist::Isotope::atom_186Os: return 0.0;
			case nist::Isotope::atom_187Os: return 0.5;
			case nist::Isotope::atom_188Os: return 0.0;
			case nist::Isotope::atom_189Os: return 1.5;
			case nist::Isotope::atom_190Os: return 0.0;
			case nist::Isotope::atom_192Os: return 0.0;
			case nist::Isotope::atom_191Ir: return 1.5;
			case nist::Isotope::atom_193Ir: return 1.5;
			case nist::Isotope::atom_190Pt: return 0.0;
			case nist::Isotope::atom_192Pt: return 0.0;
			case nist::Isotope::atom_194Pt: return 0.0;
			case nist::Isotope::atom_195Pt: return 0.5;
			case nist::Isotope::atom_196Pt: return 0.0;
			case nist::Isotope::atom_198Pt: return 0.0;
			case nist::Isotope::atom_197Au: return 1.5;
			case nist::Isotope::atom_196Hg: return 0.0;
			case nist::Isotope::atom_198Hg: return 0.0;
			case nist::Isotope::atom_199Hg: return 0.5;
			case nist::Isotope::atom_200Hg: return 0.0;
			case nist::Isotope::atom_201Hg: return 1.5;
			case nist::Isotope::atom_202Hg: return 0.0;
			case nist::Isotope::atom_204Hg: return 0.0;
			case nist::Isotope::atom_203Tl: return 0.5;
			case nist::Isotope::atom_204Tl: return 2.0;
			case nist::Isotope::atom_205Tl: return 0.5;
			case nist::Isotope::atom_204Pb: return 0.0;
			case nist::Isotope::atom_206Pb: return 0.0;
			case nist::Isotope::atom_207Pb: return 0.5;
			case nist::Isotope::atom_208Pb: return 0.0;
			case nist::Isotope::atom_207Bi: return 4.5;
			case nist::Isotope::atom_209Bi: return 4.5;
			case nist::Isotope::atom_209Po: return 0.5;
			case nist::Isotope::atom_227Ac: return 1.5;
			case nist::Isotope::atom_229Th: return 2.5;
			case nist::Isotope::atom_232Th: return 0.0;
			case nist::Isotope::atom_231Pa: return 1.5;
			case nist::Isotope::atom_234U:  return 0.0;
			case nist::Isotope::atom_235U:  return 3.5;
			case nist::Isotope::atom_238U:  return 0.0;
			case nist::Isotope::atom_237Np: return 2.5;
			case nist::Isotope::atom_239Pu: return 0.5;
			case nist::Isotope::atom_243Am: return 2.5;

			// NOTE: Since not all isotopes are covered and returning zero nuclear
			// spins as default would be misleading, not providing a valid isotope
			// is considered a fatal error. More entries should be added on demand.

			default:
			print::error(WHERE, "Invalid isotope ", nist::atomic_symbol(a));
		}

		// NOTE: Unreachable.
		return 0.0;
	}

	static inline u32 atomic_number(c_str symbol)
	{
		auto as_enum = nist::isotope_enum(symbol);
		return nist::atomic_number(as_enum);
	}

	enum class Orbital: u8 {
		s = 0,   // l = 0, m =  0
		pz,      // l = 1, m =  0
		px,      // l = 1, m = -1
		py,      // l = 1, m = +1
		dzz,     // l = 2, m =  0
		dxz,     // l = 2, m = -1
		dyz,     // l = 2, m = +1
		dxy,     // l = 2, m = -2
		dxxyy,   // l = 2, m = +2
		fzzz,    // l = 3, m =  0
		fxzz,    // l = 3, m = -1
		fyzz,    // l = 3, m = +1
		fxyz,    // l = 3, m = -2
		fzxxzyy, // l = 3, m = +2, NOTE: z(xx - yy)
		fxxxxyy, // l = 3, m = -3, NOTE: x(xx - 3yy)
		fyxxyyy, // l = 3, m = +3, NOTE: y(3xx - yy)
		unknown
	};

	static constexpr usize MAX_ORBITAL_COUNT = as_usize(nist::Orbital::unknown);
}
