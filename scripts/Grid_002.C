// Mainframe macro generated from application: root.exe
// By ROOT version 6.18/04 on 2020-05-09 22:50:02

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolTip
#include "TGToolTip.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif

#include "Riostream.h"


class TJobSub {

public:

  TGMainFrame*        fMainFrame;

  struct Gui_t {
    TGTextEntry*   fInputStage;
    TGTextEntry*   fStage;
    TGTextEntry*   fTime;
    TGTextEntry*   fExtraParameters;
  } fGui;

  TString   fProject;
  TString   fDsid;

  TJobSub(const char* Project, const char* Dsid, const TGWindow *p, UInt_t w, UInt_t h);

  virtual ~TJobSub();

  void     BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height);
  void     ExecuteCommand(const char* Cmd, int PrintOnly = 0);

  void     gridexport();

  void     check_grid_output  ();
  void     list_pnfs_files    ();
  void     move_stage_output  ();
  void     move_dset_to_dcache();

  void     submit_stnmaker_job();
  void     catalog_stntuples  ();

  void     gen_fcl();
  void     submit_grid_job();
  void     jobsub_q();
  
  ClassDef(TJobSub, 0)
};

//-----------------------------------------------------------------------------
TJobSub::TJobSub(const char* Project, const char* Dsid, const TGWindow *p, UInt_t w, UInt_t h) {
  fProject = Project;
  fDsid    = Dsid;
  BuildGui(p, w, h);
}

//-----------------------------------------------------------------------------
TJobSub::~TJobSub() {
   fMainFrame->Cleanup();
}

//-----------------------------------------------------------------------------
void TJobSub::ExecuteCommand(const char* Cmd, int PrintOnly) {
  printf(">> TJobSub::ExecuteCommand : executing cmd: %s\n",Cmd);

  if (PrintOnly != 1) {
    char buf[10001];
    FILE* pipe = gSystem->OpenPipe(Cmd,"r");
    while (fgets(buf,10000,pipe)) { printf("%s",buf); }
    gSystem->ClosePipe(pipe);
  }

  printf(">> TJobSub::ExecuteCommand : DONE\n");
}

//-----------------------------------------------------------------------------
void TJobSub::move_stage_output() {
  TString cmd;

  cmd = Form("%s/scripts/move_stage_output %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
void TJobSub::move_dset_to_dcache() {
  TString cmd;

  cmd = Form("%s/scripts/move_dset_to_dcache %s %s %s %s .: NOT IMPLEMENTED YET!",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText());

  int print_only = 1;
  ExecuteCommand(cmd.Data(),print_only);
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TJobSub::check_grid_output() {
  TString cmd;

  cmd = Form("%s/scripts/check_grid_output %s %s %s %s %s",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText(),
	     fGui.fExtraParameters->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TJobSub::list_pnfs_files() {
  TString cmd;

  cmd = Form("%s/scripts/list_pnfs_files %s %s %s %s %s",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText(),
	     fGui.fExtraParameters->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TJobSub::jobsub_q() {
  TString cmd;

  cmd = Form("date; time jobsub_q --user murat");

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// generate fcl
//-----------------------------------------------------------------------------
void TJobSub::gen_fcl() {
  TString cmd;

  cmd = Form("%s/scripts/gen_fcl %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
void TJobSub::submit_grid_job() {
  TString cmd;

  cmd = Form("%s/scripts/submit_grid_job %s %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText(),
	     fGui.fTime->GetText());

  TDatime x;
  TString istage = fGui.fInputStage->GetText();
  TString jstage = fGui.fStage->GetText();
  TString time   = fGui.fTime->GetText();

  istage.ReplaceAll(':','_');
  jstage.ReplaceAll(':','_');

  printf("* <%s> * SUBMITTED* : %s.%s.%s.%s      %s \n",x.AsSQLString(),fProject.Data(),fDsid.Data(),istage.Data(),jstage.Data(),fGui.fTime->GetText());
  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// so far, assume running interactively, otherwise - submit grid job 
//-----------------------------------------------------------------------------
void TJobSub::submit_stnmaker_job() {
  TString cmd;

  cmd = Form("%s/scripts/submit_stnmaker_job %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText());

  // TDatime x;
  // TString istage = fGui.fInputStage->GetText();
  // TString jstage = fGui.fStage->GetText();

  // istage.ReplaceAll(':','_');
  // jstage.ReplaceAll(':','_');
  //
  //  printf("* <%s> * SUBMITTED* : %s.%s.%s.%s      %s \n",x.AsSQLString(),fProject.Data(),fDsid.Data(),istage.Data(),jstage.Data(),fGui.fTime->GetText());
  // int print_only = 1; // debug first !
  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// so far, always an interactive command
//-----------------------------------------------------------------------------
void TJobSub::catalog_stntuples() {
  TString cmd;


  //  Stntuple/scripts/catalog_stntuples --bluearc -b ts_warm_bore -d ${dsid}_s3_tgtstops -p .nts.murat -D /mu2e/data/users/murat/datasets/ts_warm_bore/$dsid/s3_stn_tgtstops --install  ;

  TString istage = fGui.fInputStage->GetText();
  istage.ReplaceAll(':','_');

  TObjArray* ist = istage.Tokenize(":");
  TObjString* input_stage = (TObjString*) ist->At(0);

  TString jstage = fGui.fStage->GetText();
  jstage.ReplaceAll(':','_');

  cmd = Form("Stntuple/scripts/catalog_stntuples --bluearc -b %s -d %s_%s -p nts.murat -D /mu2e/data/users/murat/datasets/%s/%s/%s_%s --install %s",
	     fProject.Data(),
	     fDsid.Data(),istage.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     input_stage->GetString().Data(),
	     jstage.Data(),
	     "/publicweb/m/murat/cafdfc");

  int print_only = 1; // debug first !
  ExecuteCommand(cmd.Data(),print_only);
}

//-----------------------------------------------------------------------------
void TJobSub::BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height) {
//-----------------------------------------------------------------------------
// main frame
//-----------------------------------------------------------------------------
   fMainFrame = new TGMainFrame(gClient->GetRoot(),Width,Height,kMainFrame | kVerticalFrame);
   fMainFrame->SetName("MainFrame");
   fMainFrame->SetLayoutBroken(kTRUE);
//-----------------------------------------------------------------------------
// left subframe - labels and text entries
//-----------------------------------------------------------------------------
   // "fGroupFrameParameters" group frame
   TGGroupFrame *fGroupFrameParameters = new TGGroupFrame(fMainFrame,Form("%s:%s",fProject.Data(),fDsid.Data()));
   fGroupFrameParameters->SetLayoutBroken(kTRUE);

   TGLabel *fLabel1955 = new TGLabel(fGroupFrameParameters,"Stage");
   fLabel1955->SetTextJustify(36);
   fLabel1955->SetMargins(0,0,0,0);
   fLabel1955->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1955, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1955->MoveResize(10,20,80,24);

   TGLabel *fLabel1948 = new TGLabel(fGroupFrameParameters,"Input Stage");
   fLabel1948->SetTextJustify(36);
   fLabel1948->SetMargins(0,0,0,0);
   fLabel1948->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1948, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1948->MoveResize(10,50,80,24);

   TGLabel *fLabel1962 = new TGLabel(fGroupFrameParameters,"Time/xrootd");
   fLabel1962->SetTextJustify(36);
   fLabel1962->SetMargins(0,0,0,0);
   fLabel1962->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1962, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1962->MoveResize(10,80,80,24);

   TGLabel *fLabel2027 = new TGLabel(fGroupFrameParameters,"Extra Pars");
   fLabel2027->SetTextJustify(36);
   fLabel2027->SetMargins(0,0,0,0);
   fLabel2027->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel2027, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel2027->MoveResize(10,110,80,24);
//-----------------------------------------------------------------------------
// text entries
//-----------------------------------------------------------------------------
   TGFont *ufont;         // will reflect user font changes
   ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   TGGC   *uGC;           // will reflect user GC changes

					// graphics context changes
   GCValues_t valEntry_uGC;
   valEntry_uGC.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   gClient->GetColorByName("#000000",valEntry_uGC.fForeground);
   gClient->GetColorByName("#e8e8e8",valEntry_uGC.fBackground);
   valEntry_uGC.fFillStyle = kFillSolid;
   valEntry_uGC.fFont = ufont->GetFontHandle();
   valEntry_uGC.fGraphicsExposures = kFALSE;
   uGC = gClient->GetGC(&valEntry_uGC, kTRUE);

   fGui.fInputStage = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fInputStage->SetMaxLength(4096);
   fGui.fInputStage->SetAlignment(kTextLeft);
   fGui.fInputStage->SetText("s1:mubeam");
   fGui.fInputStage->Resize(112,fGui.fInputStage->GetDefaultHeight());
   fGui.fInputStage->MoveResize(120,20,110,24);
   fGroupFrameParameters->AddFrame(fGui.fInputStage, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   fGui.fStage = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fStage->SetMaxLength(4096);
   fGui.fStage->SetAlignment(kTextLeft);
   fGui.fStage->SetText("s2:sim");
   fGui.fStage->Resize(112,fGui.fStage->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fStage, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fStage->MoveResize(120,50,110,24);

   fGui.fTime = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fTime->SetMaxLength(4096);
   fGui.fTime->SetAlignment(kTextLeft);
   fGui.fTime->SetText("3h:xrootd");
   fGui.fTime->Resize(112,fGui.fTime->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fTime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fTime->MoveResize(120,80,110,24);

   fGui.fExtraParameters = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fExtraParameters->SetMaxLength(4096);
   fGui.fExtraParameters->SetAlignment(kTextLeft);
   fGui.fExtraParameters->SetText(".");
   fGui.fExtraParameters->Resize(104,fGui.fExtraParameters->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fExtraParameters, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fExtraParameters->MoveResize(120,110,110,24);

   // TGHorizontal3DLine *fHorizontal3DLine2566 = new TGHorizontal3DLine(fGroupFrameParameters,208,1);
   // fGroupFrameParameters->AddFrame(fHorizontal3DLine2566, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fHorizontal3DLine2566->MoveResize(24,64,208,1);

   // TGHorizontal3DLine *fHorizontal3DLine2579 = new TGHorizontal3DLine(fGroupFrameParameters,200,1);
   // fGroupFrameParameters->AddFrame(fHorizontal3DLine2579, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fHorizontal3DLine2579->MoveResize(24,120,200,1);

   // TGHorizontal3DLine *fHorizontal3DLine2704 = new TGHorizontal3DLine(fGroupFrameParameters,208,8);
   // fGroupFrameParameters->AddFrame(fHorizontal3DLine2704, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fHorizontal3DLine2704->MoveResize(24,184,208,8);

   fGroupFrameParameters->SetLayoutManager(new TGVerticalLayout(fGroupFrameParameters));
   fMainFrame->AddFrame(fGroupFrameParameters, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGroupFrameParameters->MoveResize(10,15,250,150);

//-----------------------------------------------------------------------------
// central text entry group frame
//-----------------------------------------------------------------------------
   // // "fCentralFrame" group frame
   // TGGroupFrame *fCentralFrame = new TGGroupFrame(fMainFrame,"Central");
   // fCentralFrame->SetLayoutBroken(kTRUE);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes

   // GCValues_t valEntry1973;
   // valEntry1973.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1973.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1973.fBackground);
   // valEntry1973.fFillStyle = kFillSolid;
   // valEntry1973.fFont = ufont->GetFontHandle();
   // valEntry1973.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1973, kTRUE);

   // TGTextEntry *fTextEntry1973 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1973->SetMaxLength(4096);
   // fTextEntry1973->SetAlignment(kTextLeft);
   // fTextEntry1973->SetText("fTextEntry1973");
   // fTextEntry1973->Resize(200,fTextEntry1973->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1973, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1973->MoveResize(24,32,200,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry1980;
   // valEntry1980.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1980.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1980.fBackground);
   // valEntry1980.fFillStyle = kFillSolid;
   // valEntry1980.fFont = ufont->GetFontHandle();
   // valEntry1980.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1980, kTRUE);
   // TGTextEntry *fTextEntry1980 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1980->SetMaxLength(4096);
   // fTextEntry1980->SetAlignment(kTextLeft);
   // fTextEntry1980->SetText("fTextEntry1980");
   // fTextEntry1980->Resize(200,fTextEntry1980->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1980, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1980->MoveResize(24,88,200,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry1987;
   // valEntry1987.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1987.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1987.fBackground);
   // valEntry1987.fFillStyle = kFillSolid;
   // valEntry1987.fFont = ufont->GetFontHandle();
   // valEntry1987.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1987, kTRUE);
   // TGTextEntry *fTextEntry1987 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1987->SetMaxLength(4096);
   // fTextEntry1987->SetAlignment(kTextLeft);
   // fTextEntry1987->SetText("fTextEntry1987");
   // fTextEntry1987->Resize(208,fTextEntry1987->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1987, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1987->MoveResize(24,152,208,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry1994;
   // valEntry1994.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1994.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1994.fBackground);
   // valEntry1994.fFillStyle = kFillSolid;
   // valEntry1994.fFont = ufont->GetFontHandle();
   // valEntry1994.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1994, kTRUE);
   // TGTextEntry *fTextEntry1994 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1994->SetMaxLength(4096);
   // fTextEntry1994->SetAlignment(kTextLeft);
   // fTextEntry1994->SetText("fTextEntry1994");
   // fTextEntry1994->Resize(208,fTextEntry1994->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1994, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1994->MoveResize(24,200,208,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry2001;
   // valEntry2001.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry2001.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry2001.fBackground);
   // valEntry2001.fFillStyle = kFillSolid;
   // valEntry2001.fFont = ufont->GetFontHandle();
   // valEntry2001.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry2001, kTRUE);
   // TGTextEntry *fTextEntry2001 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry2001->SetMaxLength(4096);
   // fTextEntry2001->SetAlignment(kTextLeft);
   // fTextEntry2001->SetText("fTextEntry2001");
   // fTextEntry2001->Resize(192,fTextEntry2001->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry2001, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry2001->MoveResize(32,254,192,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry2020;
   // valEntry2020.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry2020.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry2020.fBackground);
   // valEntry2020.fFillStyle = kFillSolid;
   // valEntry2020.fFont = ufont->GetFontHandle();
   // valEntry2020.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry2020, kTRUE);
   // TGTextEntry *fTextEntry2020 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry2020->SetMaxLength(4096);
   // fTextEntry2020->SetAlignment(kTextLeft);
   // fTextEntry2020->SetText("fTextEntry2020");
   // fTextEntry2020->Resize(192,fTextEntry2020->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry2020, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry2020->MoveResize(32,296,192,22);

   // fCentralFrame->SetLayoutManager(new TGVerticalLayout(fCentralFrame));
   // fCentralFrame->Resize(250,360);
   // fMainFrame->AddFrame(fCentralFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fCentralFrame->MoveResize(600,20,250,360);

//-----------------------------------------------------------------------------
// "fButtons" group frame
//-----------------------------------------------------------------------------
   TGGroupFrame *fButtons = new TGGroupFrame(fMainFrame,"Commands");
   fButtons->SetLayoutBroken(kTRUE);

   TGTextButton *fTextButton = new TGTextButton(fButtons,"gen_fcl",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   // fTextButton->Resize(200,24);
   fTextButton->MoveResize(10,20,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "gen_fcl()");

   fTextButton = new TGTextButton(fButtons,"submit_grid_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   //   fTextButton->Resize(200,24);
   fTextButton->MoveResize(10,50,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "submit_grid_job()");

   fTextButton = new TGTextButton(fButtons,"move_dset_to_dcache",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->MoveResize(10,80,200,24);
   fTextButton->Connect("Pressed()", "TJobSub", this, "move_dset_to_dcache()");

   fTextButton = new TGTextButton(fButtons,"check_grid_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->MoveResize(10,110,200,24);
   fTextButton->Connect("Pressed()", "TJobSub", this, "check_grid_output()");

   fTextButton = new TGTextButton(fButtons,"move_stage_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->MoveResize(10,140,200,24);
   fTextButton->Connect("Pressed()", "TJobSub", this, "move_stage_output()");
   
   fTextButton = new TGTextButton(fButtons,"copy_log_files",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,170,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   fTextButton = new TGTextButton(fButtons,"list_pnfs_files",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,200,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "list_pnfs_files()");

   fTextButton = new TGTextButton(fButtons,"submit_stnmaker_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,230,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "submit_stnmaker_job()");

   fTextButton = new TGTextButton(fButtons,"catalog_stntuples",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,260,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "catalog_stntuples()");

   fTextButton = new TGTextButton(fButtons,"jobsub_q",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->MoveResize(10,290,200,24);
   fTextButton->Connect("Pressed()", "TJobSub", this, "jobsub_q()");

   fButtons->SetLayoutManager(new TGVerticalLayout(fButtons));
   fMainFrame->AddFrame(fButtons, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fButtons->MoveResize(280,20,220,330);

   fMainFrame->SetMWMHints(kMWMDecorAll,
                        kMWMFuncAll,
                        kMWMInputModeless);
   fMainFrame->MapSubwindows();

   fMainFrame->Resize(fMainFrame->GetDefaultSize());
   fMainFrame->MapWindow();
   fMainFrame->Resize(510,360);
   //   fMainFrame->GetMainFrame()->SetName("emoe");
}  


//-----------------------------------------------------------------------------
void Grid_002(const char* DsID) {
  TJobSub* x = new TJobSub("ts_warm_bore",DsID,gClient->GetRoot(),150,300);
}

