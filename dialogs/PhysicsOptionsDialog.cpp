#include "stdafx.h"
#include "resource.h"
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <fstream>
#include <sstream>
#include "PhysicsOptionsDialog.h"

using namespace rapidxml;

constexpr unsigned int num_physicsoptions = 8;
static char * physicsoptions[num_physicsoptions] ={ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
static unsigned int physicsselection = 0;


PhysicsOptionsDialog::PhysicsOptionsDialog() : CDialog(IDD_PHYSICS_OPTIONS)
{
}

BOOL PhysicsOptionsDialog::OnInitDialog()
{
    const HWND hwndList = GetDlgItem(IDC_PhysicsList).GetHwnd();

    const size_t size = SendMessage(hwndList, LB_GETCOUNT, 0, 0);
    for (size_t i = 0; i < size; i++)
    {
        if (physicsoptions[i])
        {
            delete[] physicsoptions[i];
            physicsoptions[i] = nullptr;
        }
        const int* sd = (int *)SendMessage(hwndList, LB_GETITEMDATA, i, 0);
        delete sd;
    }

    SendMessage(hwndList, WM_SETREDRAW, FALSE, 0); // to speed up adding the entries :/
    SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
    for (unsigned int i = 0; i < num_physicsoptions; i++)
    {
        physicsoptions[i] = new char[256];
        char tmp[256];
        sprintf_s(tmp, sizeof(tmp), "PhysicsSetName%u", i);
        if (LoadValue(regKey[RegName::Player], tmp, physicsoptions[i], 256) != S_OK)
            sprintf_s(physicsoptions[i], 256, "Set %u", i + 1);
        sprintf_s(tmp, sizeof(tmp), "%u: %s", i + 1, physicsoptions[i]);
        const size_t index = SendMessage(hwndList, LB_ADDSTRING, 0, (size_t)tmp);
        int * const sd = new int;
        *sd = i;
        SendMessage(hwndList, LB_SETITEMDATA, index, (LPARAM)sd);
    }
    SendMessage(hwndList, LB_SETCURSEL, physicsselection, 0);
    SendMessage(hwndList, WM_SETREDRAW, TRUE, 0);

    const float FlipperPhysicsMass = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsMass" + std::to_string(physicsselection), 1.f);
    SetItemText(DISPID_Flipper_Speed, FlipperPhysicsMass);
    const float FlipperPhysicsStrength = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsStrength" + std::to_string(physicsselection), 2200.f);
    SetItemText(19, FlipperPhysicsStrength);
    const float FlipperPhysicsElasticity = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsElasticity" + std::to_string(physicsselection), 0.8f);
    SetItemText(21, FlipperPhysicsElasticity);
    const float FlipperPhysicsScatter = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsScatter" + std::to_string(physicsselection), 0.f);
    SetItemText(112, FlipperPhysicsScatter);
    const float FlipperPhysicsTorqueDamping = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsEOSTorque" + std::to_string(physicsselection), 0.75f);
    SetItemText(113, FlipperPhysicsTorqueDamping);
    const float FlipperPhysicsTorqueDampingAngle = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsEOSTorqueAngle" + std::to_string(physicsselection), 6.f);
    SetItemText(189, FlipperPhysicsTorqueDampingAngle);
    const float FlipperPhysicsReturnStrength = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsReturnStrength" + std::to_string(physicsselection), 0.058f);
    SetItemText(23, FlipperPhysicsReturnStrength);
    const float FlipperPhysicsElasticityFalloff = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsElasticityFalloff" + std::to_string(physicsselection), 0.43f);
    SetItemText(22, FlipperPhysicsElasticityFalloff);
    const float FlipperPhysicsFriction = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsFriction" + std::to_string(physicsselection), 0.6f);
    SetItemText(109, FlipperPhysicsFriction);
    const float FlipperPhysicsCoilRampUp = LoadValueFloatWithDefault(regKey[RegName::Player], "FlipperPhysicsCoilRampUp" + std::to_string(physicsselection), 3.f);
    SetItemText(110, FlipperPhysicsCoilRampUp);
    const float TablePhysicsGravityConstant = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsGravityConstant" + std::to_string(physicsselection), DEFAULT_TABLE_GRAVITY);
    SetItemText(1100, TablePhysicsGravityConstant);
    const float TablePhysicsContactFriction = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsContactFriction"+std::to_string(physicsselection), DEFAULT_TABLE_CONTACTFRICTION);
    SetItemText(1101, TablePhysicsContactFriction);
    const float TablePhysicsElasticity = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsElasticity" + std::to_string(physicsselection), DEFAULT_TABLE_ELASTICITY);
    SetItemText(1708, TablePhysicsElasticity);
    const float TablePhysicsElasticityFalloff = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsElasticityFalloff"+std::to_string(physicsselection), DEFAULT_TABLE_ELASTICITY_FALLOFF);
    SetItemText(1709, TablePhysicsElasticityFalloff);
    const float TablePhysicsScatterAngle = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsScatterAngle" + std::to_string(physicsselection), DEFAULT_TABLE_PFSCATTERANGLE);
    SetItemText(1710, TablePhysicsScatterAngle);
    const float TablePhysicsContactScatterAngle = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsContactScatterAngle"+std::to_string(physicsselection), DEFAULT_TABLE_SCATTERANGLE);
    SetItemText(1102, TablePhysicsContactScatterAngle);
    const float TablePhysicsMinSlope = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsMinSlope" + std::to_string(physicsselection), DEFAULT_TABLE_MIN_SLOPE);
    SetItemText(1103, TablePhysicsMinSlope);
    const float TablePhysicsMaxSlope = LoadValueFloatWithDefault(regKey[RegName::Player], "TablePhysicsMaxSlope" + std::to_string(physicsselection), DEFAULT_TABLE_MAX_SLOPE);
    SetItemText(1104, TablePhysicsMaxSlope);

    SetDlgItemText(1110, physicsoptions[physicsselection]);

    return TRUE;
}

INT_PTR PhysicsOptionsDialog::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DialogProcDefault(uMsg, wParam, lParam);
}

struct PhysValues
{
    char gravityConstant[16];
    char contactFriction[16];
    char tableElasticity[16];
    char tableElasticityFalloff[16];
    char playfieldScatter[16];
    char defaultElementScatter[16];
    // Flipper:
    char speed[16];
    char strength[16];
    char elasticity[16];
    char scatter[16];
    char eosTorque[16];
    char eosTorqueAngle[16];
    char returnStrength[16];
    char elasticityFalloff[16];
    char friction[16];
    char coilRampup[16];

    char minSlope[16];
    char maxSlope[16];
    char name[MAXNAMEBUFFER];
};

static PhysValues loadValues;


BOOL PhysicsOptionsDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch(HIWORD(wParam))
    {
        case LBN_SELCHANGE:
        {
            const HWND hwndList = GetDlgItem(IDC_PhysicsList).GetHwnd();

            const size_t tmp = SendMessage(hwndList, LB_GETCURSEL, 0, 0);

            if (tmp != physicsselection)
            {
                int result = g_pvp->MessageBox("Save", "Save current physics set?", MB_YESNOCANCEL | MB_ICONQUESTION);
                if (result == IDYES)
                    SaveCurrentPhysicsSetting();

                if (result != IDCANCEL)
                {
                    physicsselection = (unsigned int)tmp;
                    SendMessage(WM_INITDIALOG, 0, 0); // reinit all boxes
                }
                else
                    ::SendMessage(hwndList, LB_SETCURSEL, physicsselection, 0);
            }
            break;
        }
    }
    switch(LOWORD(wParam))
    {
        case 1111:
        {
            if (LoadSetting() == false)
                break;

            SetDlgItemText(1100, CString(loadValues.gravityConstant));
            SetDlgItemText(1101, CString(loadValues.contactFriction));
            SetDlgItemText(1708, CString(loadValues.tableElasticity));
            SetDlgItemText(1709, CString(loadValues.tableElasticityFalloff));
            SetDlgItemText(1710, CString(loadValues.playfieldScatter));
            SetDlgItemText(1102, CString(loadValues.defaultElementScatter));
            SetDlgItemText(1103, CString(loadValues.minSlope));
            SetDlgItemText(1104, CString(loadValues.maxSlope));

            SetDlgItemText(DISPID_Flipper_Speed, CString(loadValues.speed));
            SetDlgItemText(19, CString(loadValues.strength));
            SetDlgItemText(21, CString(loadValues.elasticity));
            SetDlgItemText(112, CString(loadValues.scatter));
            SetDlgItemText(113, CString(loadValues.eosTorque));
            SetDlgItemText(189, CString(loadValues.eosTorqueAngle));
            SetDlgItemText(23, CString(loadValues.returnStrength));
            SetDlgItemText(22, CString(loadValues.elasticityFalloff));
            SetDlgItemText(109, CString(loadValues.friction));
            SetDlgItemText(110, CString(loadValues.coilRampup));

            SetDlgItemText(1110, CString(loadValues.name));
            SetFocus();
            break;
        }
        case 1112:
        {
            char szFileName[MAXSTRING];
            /*CComObject<PinTable>* const pt = g_pvp->GetActiveTable();
            if (pt)
            {
               strncpy_s(szFileName, pt->m_szFileName.c_str(), sizeof(szFileName)-1);
               const size_t idx = pt->m_szFileName.find_last_of('.');
               if (idx != string::npos && idx < MAXSTRING)
                  szFileName[idx] = '\0';
            }
            else
               szFileName[0] = '\0';*/
            strncpy_s(szFileName, "Physics.vpp", sizeof(szFileName)-1);

            OPENFILENAME ofn = {};
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hInstance = g_pvp->theInstance;
            ofn.hwndOwner = g_pvp->GetHwnd();
            // TEXT
            ofn.lpstrFilter = "Visual Pinball Physics (*.vpp)\0*.vpp\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = sizeof(szFileName);
            ofn.lpstrDefExt = "vpp";
            ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

            string szInitialDir;
            const HRESULT hr = LoadValue(regKey[RegName::RecentDir], "PhysicsDir"s, szInitialDir);
            if (hr != S_OK)
               szInitialDir = "c:\\Visual Pinball\\Tables\\";

            ofn.lpstrInitialDir = szInitialDir.c_str();

            const int ret = GetSaveFileName(&ofn);
            if (ret == 0)
                break;

            const string szFilename(ofn.lpstrFile);
            const size_t index = szFilename.find_last_of('\\');
            if (index != string::npos)
            {
                const string newInitDir(szFilename.substr(0, index));
                SaveValue(regKey[RegName::RecentDir], "PhysicsDir"s, newInitDir);
            }

            xml_document<> xmlDoc;
            xml_node<>*dcl = xmlDoc.allocate_node(node_declaration);
            dcl->append_attribute(xmlDoc.allocate_attribute("version", "1.0"));
            dcl->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8"));
            xmlDoc.append_node(dcl);

            //root node
            xml_node<>*root = xmlDoc.allocate_node(node_element, "physics");
            xml_node<>*flipper = xmlDoc.allocate_node(node_element, "flipper");
            xml_node<>*table = xmlDoc.allocate_node(node_element, "table");

            const string fs(GetItemText(DISPID_Flipper_Speed));
            xml_node<>*flipSpeed = xmlDoc.allocate_node(node_element, "speed", fs.c_str());
            flipper->append_node(flipSpeed);

            const string fps(GetItemText(19));
            xml_node<>*flipPhysStrength = xmlDoc.allocate_node(node_element, "strength", fps.c_str());
            flipper->append_node(flipPhysStrength);

            const string fe(GetItemText(21));
            xml_node<>*flipElasticity = xmlDoc.allocate_node(node_element, "elasticity", fe.c_str());
            flipper->append_node(flipElasticity);

            const string fsc(GetItemText(112));
            xml_node<>*flipScatter = xmlDoc.allocate_node(node_element, "scatter", fsc.c_str());
            flipper->append_node(flipScatter);

            const string ftd(GetItemText(113));
            xml_node<>*flipTorqueDamping = xmlDoc.allocate_node(node_element, "eosTorque", ftd.c_str());
            flipper->append_node(flipTorqueDamping);

            const string ftda(GetItemText(189));
            xml_node<>*flipTorqueDampingAngle = xmlDoc.allocate_node(node_element, "eosTorqueAngle", ftda.c_str());
            flipper->append_node(flipTorqueDampingAngle);

            const string frs(GetItemText(23));
            xml_node<>*flipReturnStrength = xmlDoc.allocate_node(node_element, "returnStrength", frs.c_str());
            flipper->append_node(flipReturnStrength);

            const string fef(GetItemText(22));
            xml_node<>*flipElasticityFalloff = xmlDoc.allocate_node(node_element, "elasticityFalloff", fef.c_str());
            flipper->append_node(flipElasticityFalloff);

            const string ff(GetItemText(109));
            xml_node<>*flipfriction = xmlDoc.allocate_node(node_element, "friction", ff.c_str());
            flipper->append_node(flipfriction);

            const string fcru(GetItemText(110));
            xml_node<>*flipCoilRampUp = xmlDoc.allocate_node(node_element, "coilRampUp", fcru.c_str());
            flipper->append_node(flipCoilRampUp);

            const string tgc(GetItemText(1100));
            xml_node<>*tabGravityConst = xmlDoc.allocate_node(node_element, "gravityConstant", tgc.c_str());
            table->append_node(tabGravityConst);

            const string tcf(GetItemText(1101));
            xml_node<>*tabContactFriction = xmlDoc.allocate_node(node_element, "contactFriction", tcf.c_str());
            table->append_node(tabContactFriction);

            const string te(GetItemText(1708));
            xml_node<>*tabElasticity = xmlDoc.allocate_node(node_element, "elasticity", te.c_str());
            table->append_node(tabElasticity);

            const string tef(GetItemText(1709));
            xml_node<>*tabElasticityFalloff = xmlDoc.allocate_node(node_element, "elasticityFalloff", tef.c_str());
            table->append_node(tabElasticityFalloff);

            const string tsa(GetItemText(1710));
            xml_node<>*tabScatterAngle = xmlDoc.allocate_node(node_element, "playfieldScatter", tsa.c_str());
            table->append_node(tabScatterAngle);

            const string tcsa(GetItemText(1102));
            xml_node<>*tabContactScatterAngle = xmlDoc.allocate_node(node_element, "defaultElementScatter", tcsa.c_str());
            table->append_node(tabContactScatterAngle);

            const string tmns(GetItemText(1103));
            xml_node<>*tabMinSlope = xmlDoc.allocate_node(node_element, "playfieldminslope", tmns.c_str());
            table->append_node(tabMinSlope);

            const string tmxs(GetItemText(1104));
            xml_node<>*tabMaxSlope = xmlDoc.allocate_node(node_element, "playfieldmaxslope", tmxs.c_str());
            table->append_node(tabMaxSlope);

            const string sn(GetItemText(1110));
            xml_node<>*settingName = xmlDoc.allocate_node(node_element, "name", sn.c_str());
            root->append_node(settingName);

            root->append_node(table);
            root->append_node(flipper);
            xmlDoc.append_node(root);

            std::ofstream myfile(ofn.lpstrFile);
            myfile << xmlDoc;
            myfile.close();

            SetFocus();

            break;
        }

        default:
        return FALSE;
    }
    return TRUE;
}

void PhysicsOptionsDialog::OnOK()
{
    SaveCurrentPhysicsSetting();
    CDialog::OnOK();
}

void PhysicsOptionsDialog::OnDestroy()
{
    const HWND hwndList = GetDlgItem(IDC_PhysicsList).GetHwnd();
    const size_t size = ::SendMessage(hwndList, LB_GETCOUNT, 0, 0);
    for (size_t i = 0; i < size; i++)
    {
        if (physicsoptions[i])
        {
            delete[] physicsoptions[i];
            physicsoptions[i] = nullptr;
        }
        const int* sd = (int *)::SendMessage(hwndList, LB_GETITEMDATA, i, 0);
        delete sd;
    }
    ::SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
}

bool PhysicsOptionsDialog::LoadSetting()
{
    string szInitialDir;
    HRESULT hr = LoadValue(regKey[RegName::RecentDir], "PhysicsDir"s, szInitialDir);
    if (hr != S_OK)
        szInitialDir = "c:\\Visual Pinball\\Tables\\";

    vector<string> szFileName;
    if (!g_pvp->OpenFileDialog(szInitialDir, szFileName, "Visual Pinball Physics (*.vpp)\0*.vpp\0", "vpp", 0))
        return false;

    const size_t index = szFileName[0].find_last_of('\\');
    if (index != string::npos)
        hr = SaveValue(regKey[RegName::RecentDir], "PhysicsDir"s, szFileName[0].substr(0, index));

    xml_document<> xmlDoc;
    try
    {
        std::stringstream buffer;
        std::ifstream myFile(szFileName[0]);
        buffer << myFile.rdbuf();
        myFile.close();

        xmlDoc.parse<0>((char*)buffer.str().c_str());
        const xml_node<> *root = xmlDoc.first_node("physics");
        const xml_node<> *table = root->first_node("table");
        const xml_node<> *flipper = root->first_node("flipper");

        strncpy_s(loadValues.gravityConstant, table->first_node("gravityConstant")->value(), sizeof(loadValues.gravityConstant)-1);
        strncpy_s(loadValues.contactFriction, table->first_node("contactFriction")->value(), sizeof(loadValues.contactFriction)-1);
        strncpy_s(loadValues.tableElasticity, table->first_node("elasticity")->value(), sizeof(loadValues.tableElasticity)-1);
        strncpy_s(loadValues.tableElasticityFalloff, table->first_node("elasticityFalloff")->value(), sizeof(loadValues.tableElasticityFalloff)-1);
        strncpy_s(loadValues.playfieldScatter, table->first_node("playfieldScatter")->value(), sizeof(loadValues.playfieldScatter)-1);
        strncpy_s(loadValues.defaultElementScatter, table->first_node("defaultElementScatter")->value(), sizeof(loadValues.defaultElementScatter)-1);
        const xml_node<char> *tmp = table->first_node("playfieldminslope");
        if(tmp)
           strncpy_s(loadValues.minSlope, sizeof(loadValues.minSlope), tmp->value(), sizeof(loadValues.minSlope)-1);
        else
           sprintf_s(loadValues.minSlope, sizeof(loadValues.minSlope), "%f", DEFAULT_TABLE_MIN_SLOPE);
        tmp = table->first_node("playfieldmaxslope");
        if(tmp)
           strncpy_s(loadValues.maxSlope, sizeof(loadValues.maxSlope), tmp->value(), sizeof(loadValues.maxSlope)-1);
        else
           sprintf_s(loadValues.maxSlope, sizeof(loadValues.maxSlope), "%f", DEFAULT_TABLE_MAX_SLOPE);
        strncpy_s(loadValues.speed, flipper->first_node("speed")->value(), sizeof(loadValues.speed)-1);
        strncpy_s(loadValues.strength, flipper->first_node("strength")->value(), sizeof(loadValues.strength)-1);
        strncpy_s(loadValues.elasticity, flipper->first_node("elasticity")->value(), sizeof(loadValues.elasticity)-1);
        strncpy_s(loadValues.scatter, flipper->first_node("scatter")->value(), sizeof(loadValues.scatter)-1);
        strncpy_s(loadValues.eosTorque, flipper->first_node("eosTorque")->value(), sizeof(loadValues.eosTorque)-1);
        strncpy_s(loadValues.eosTorqueAngle, flipper->first_node("eosTorqueAngle")->value(), sizeof(loadValues.eosTorqueAngle)-1);
        strncpy_s(loadValues.returnStrength, flipper->first_node("returnStrength")->value(), sizeof(loadValues.returnStrength)-1);
        strncpy_s(loadValues.elasticityFalloff, flipper->first_node("elasticityFalloff")->value(), sizeof(loadValues.elasticityFalloff)-1);
        strncpy_s(loadValues.friction, flipper->first_node("friction")->value(), sizeof(loadValues.friction)-1);
        strncpy_s(loadValues.coilRampup, flipper->first_node("coilRampUp")->value(), sizeof(loadValues.coilRampup)-1);

        strncpy_s(loadValues.name, root->first_node("name")->value(), sizeof(loadValues.name)-1);
    }
    catch(...)
    {
        ShowError("Error parsing physics settings file");
        xmlDoc.clear();
        return false;
    }
    xmlDoc.clear();

    return true;
}

CString PhysicsOptionsDialog::GetItemText(int id)
{
    return GetDlgItemText(id);
}

void PhysicsOptionsDialog::SetItemText(int id, float value)
{
    SetDlgItemText(id, f2sz(value).c_str());
}


void PhysicsOptionsDialog::SaveCurrentPhysicsSetting()
{
    SaveValue(regKey[RegName::Player], "FlipperPhysicsMass" + std::to_string(physicsselection), GetItemText(DISPID_Flipper_Speed).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsStrength" + std::to_string(physicsselection), GetItemText(19).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsElasticity" + std::to_string(physicsselection), GetItemText(21).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsScatter" + std::to_string(physicsselection), GetItemText(112).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsEOSTorque" + std::to_string(physicsselection), GetItemText(113).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsEOSTorqueAngle" + std::to_string(physicsselection), GetItemText(189).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsReturnStrength" + std::to_string(physicsselection), GetItemText(23).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsElasticityFalloff" + std::to_string(physicsselection), GetItemText(22).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsFriction" + std::to_string(physicsselection), GetItemText(109).c_str());
    SaveValue(regKey[RegName::Player], "FlipperPhysicsCoilRampUp" + std::to_string(physicsselection), GetItemText(110).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsGravityConstant" + std::to_string(physicsselection), GetItemText(1100).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsContactFriction" + std::to_string(physicsselection), GetItemText(1101).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsElasticity" + std::to_string(physicsselection), GetItemText(1708).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsElasticityFalloff" + std::to_string(physicsselection), GetItemText(1709).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsScatterAngle" + std::to_string(physicsselection), GetItemText(1710).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsContactScatterAngle" + std::to_string(physicsselection), GetItemText(1102).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsMinSlope" + std::to_string(physicsselection), GetItemText(1103).c_str());
    SaveValue(regKey[RegName::Player], "TablePhysicsMaxSlope" + std::to_string(physicsselection), GetItemText(1104).c_str());
    SaveValue(regKey[RegName::Player], "PhysicsSetName" + std::to_string(physicsselection), GetItemText(1110).c_str());
}
