// Cheng-Chieh Peng
// read output of runForest_pp_MC,
// plot evtgen_Bmeson decay products.
// Created 2016 Mar. 10
// Last Modified 2016 Mar. 21

#include <iostream>
#include "TTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TStyle.h"
#include <TAttMarker.h>
#include <TLegend.h>

/*
	 B0 decays:
	 else if (d_DM_tag==1 && d_TauP_tag==1 && d_nuTau_tag==1){       B0_decay1=1;}
	 else if (d_DeM_tag==1 && d_TauP_tag==1 && d_nuTau_tag==1){      B0_decay1=2;}
	 else if (d_DeM_tag==1 && d_PiP_tag==1 && d_Pi0_tag==1){         B0_decay1=3;}
	 else if (d_DeM_tag==1 && d_De0_tag==1 && d_KP_tag==1){          B0_decay1=4;}
	 else if (d_DeM_tag==1 && d_a1P_tag==1 ){                        B0_decay1=5;}
	 else if (d_DeSP_tag==1 && d_DeM_tag==1){                        B0_decay1=6;}
	 else if (d_DeM_tag==1 && d_PiP_tag==2 && d_PiM_tag==1 && d_Pi0_tag==1 ){B0_decay1=7;}

*/

void evtgen_compare_plot2(){

	//	TChain *t_evtgen = new TChain("ak4PFJetAnalyzer/t");

	//	TChain *t_pythia = new TChain("ak4PFJetAnalyzer/t");	


	TFile *f_pythia = new TFile("./root/origin/HiForestAOD_pp_MC_bjets50.root");
//	TFile *f_pythia = new TFile("./root/small_sample/HiForestAOD_pp_MC_bjets50.root"); 
	TH1F *h_B0_nChargeDau_pythia = (TH1F*)f_pythia->Get("ak4PFJetAnalyzer/h_B0_chargeDaughters");
	TH1F *h_Bpm_nChargeDau_pythia = (TH1F*)f_pythia->Get("ak4PFJetAnalyzer/h_Bpm_chargeDaughters");
	TH1F *h_Bs_nChargeDau_pythia = (TH1F*)f_pythia->Get("ak4PFJetAnalyzer/h_Bs_chargeDaughters");
	TH1F *h_Bmesons_nChargeDau_pythia = (TH1F*)f_pythia->Get("ak4PFJetAnalyzer/h_Bmesons_chargeDaughters");
	TTree *t_pythia = (TTree*)f_pythia->Get("ak4PFJetAnalyzer/t");


	TFile *f_evtgen = new TFile("./root/evtgen/HiForestAOD_pp_MC_bjets50_evtgen.root");
//	TFile *f_evtgen = new TFile("./root/small_sample/HiForestAOD_pp_MC_bjets50_evtgen.root");
	TH1F *h_B0_nChargeDau_evtgen = (TH1F*)f_evtgen->Get("ak4PFJetAnalyzer/h_B0_chargeDaughters");
	TH1F *h_Bpm_nChargeDau_evtgen = (TH1F*)f_evtgen->Get("ak4PFJetAnalyzer/h_Bpm_chargeDaughters");
	TH1F *h_Bs_nChargeDau_evtgen = (TH1F*)f_evtgen->Get("ak4PFJetAnalyzer/h_Bs_chargeDaughters");
	TH1F *h_Bmesons_nChargeDau_evtgen = (TH1F*)f_evtgen->Get("ak4PFJetAnalyzer/h_Bmesons_chargeDaughters");
  TTree *t_evtgen = (TTree*)f_evtgen->Get("ak4PFJetAnalyzer/t");


	TH1F *h_B0_nChargeDau_epRatio=(TH1F*)h_B0_nChargeDau_evtgen->Clone("h_B0_nChargeDau_epRatio");
	TH1F *h_Bpm_nChargeDau_epRatio=(TH1F*)h_Bpm_nChargeDau_evtgen->Clone("h_Bpm_nChargeDau_epRatio");
	TH1F *h_Bs_nChargeDau_epRatio=(TH1F*)h_Bs_nChargeDau_evtgen->Clone("h_Bs_nChargeDau_epRatio");
	TH1F *h_Bmesons_nChargeDau_epRatio=(TH1F*)h_Bmesons_nChargeDau_evtgen->Clone("h_Bmesons_nChargeDau_epRatio");


	double B0_pythia_entries = (double)h_B0_nChargeDau_pythia->GetEntries();
	double B0_evtgen_entries = (double)h_B0_nChargeDau_evtgen->GetEntries();
	double Bpm_pythia_entries = (double)h_Bpm_nChargeDau_pythia->GetEntries();
	double Bpm_evtgen_entries = (double)h_Bpm_nChargeDau_evtgen->GetEntries();
	double Bs_pythia_entries = (double)h_Bs_nChargeDau_pythia->GetEntries();
	double Bs_evtgen_entries = (double)h_Bs_nChargeDau_evtgen->GetEntries();
	double Bmesons_pythia_entries = (double)h_Bmesons_nChargeDau_pythia->GetEntries();
	double Bmesons_evtgen_entries = (double)h_Bmesons_nChargeDau_evtgen->GetEntries();

  gStyle->SetOptStat(0);

	int ptbins = 17; 
	int ptHi =	200;
	int ptLo =	30;

	// color : Pythia6 always use color 4 , evtgen use color 2

  TH1F *h_PtCsvCut_pythia = new TH1F("h_PtCsvCut_pythia","h_PtCsvCut_pythia",ptbins,ptLo,ptHi);
  TH1F *h_PtCsvCut_evtgen = new TH1F("h_PtCsvCut_evtgen","h_PtCsvCut_evtgen",ptbins,ptLo,ptHi);
  TH1F *h_PtAllB_pythia = new TH1F("h_PtAllB_pythia","h_PtAlB_pythia",ptbins,ptLo,ptHi);
  TH1F *h_PtAllB_evtgen = new TH1F("h_PtAllB_evtgen","h_PtAllB_evtgen",ptbins,ptLo,ptHi);

	TH1F *h_PtCsvEff_pythia = new TH1F("h_PtCsvEff_pythia","h_PtCsvEff_pythia",ptbins,ptLo,ptHi);
  TH1F *h_PtCsvEff_evtgen = new TH1F("h_PtCsvEff_evtgen","h_PtCsvEff_evtgen",ptbins,ptLo,ptHi);
  TH1F *h_PtCsvEff_epRatio = new TH1F("h_PtCsvEff_epRatio","h_PtCsvEff_epRatio",ptbins,ptLo,ptHi);

	h_PtCsvCut_pythia->Sumw2();
	h_PtCsvCut_evtgen->Sumw2();
	h_PtAllB_pythia->Sumw2();
	h_PtAllB_evtgen->Sumw2();
	h_PtCsvEff_pythia->Sumw2();
	h_PtCsvEff_evtgen->Sumw2();
	h_PtCsvEff_epRatio->Sumw2();


  t_pythia->Draw("jtpt>>h_PtAllB_pythia","abs(refparton_flavor)==5");
  t_evtgen->Draw("jtpt>>h_PtAllB_evtgen","abs(refparton_flavor)==5");

  t_pythia->Draw("jtpt>>h_PtCsvCut_pythia","abs(refparton_flavor)==5 && discr_csvSimple>0.9");
  t_evtgen->Draw("jtpt>>h_PtCsvCut_evtgen","abs(refparton_flavor)==5 && discr_csvSimple>0.9");


//	h_PtCsvEff_pythia = (TH1F*)h_PtCsvCut_pythia->Clone("h_PtCsvEff_pythia");
//  h_PtCsvEff_evtgen = (TH1F*)h_PtCsvCut_evtgen->Clone("h_PtCsvEff_evtgen");
  t_pythia->Draw("jtpt>>h_PtCsvEff_pythia","abs(refparton_flavor)==5 && discr_csvSimple>0.9");
  t_evtgen->Draw("jtpt>>h_PtCsvEff_evtgen","abs(refparton_flavor)==5 && discr_csvSimple>0.9");

//  t_pythia->Draw("jtpt>>h_PtCsvEff_pythia","discr_csvSimple>0.9");
//  t_evtgen->Draw("jtpt>>h_PtCsvEff_evtgen","discr_csvSimple>0.9");


	h_PtCsvEff_pythia->Divide(h_PtAllB_pythia);
  h_PtCsvEff_evtgen->Divide(h_PtAllB_evtgen);

	h_PtCsvEff_epRatio->Divide(h_PtCsvEff_evtgen,h_PtCsvEff_pythia,1,1);


	h_PtCsvCut_pythia->SetLineColor(4);
	h_PtAllB_pythia->SetLineColor(4);
	h_PtCsvEff_pythia->SetLineColor(4);

  h_PtCsvCut_evtgen->SetLineColor(2);
  h_PtAllB_evtgen->SetLineColor(2);
  h_PtCsvEff_evtgen->SetLineColor(2);


	TCanvas *C_CSVtagging = new TCanvas("C_CSVtagging","C_CSVtagging");
	C_CSVtagging->Divide(1,2);
	C_CSVtagging->cd(1);
	h_PtCsvEff_pythia->SetMaximum(0.7);
	h_PtCsvEff_pythia->SetTitle("Csv Tagging Efficiency");
	h_PtCsvEff_pythia->GetXaxis()->SetTitle("JetPt");
	h_PtCsvEff_pythia->Draw();
	h_PtCsvEff_evtgen->Draw("SAME");

  TLegend *leg_CSVtagging1 = new TLegend(0.75,0.75,0.9,0.9);
  //  leg->SetHeader("header");
  leg_CSVtagging1->AddEntry(h_PtCsvEff_pythia,"pythia6","l");
  leg_CSVtagging1->AddEntry(h_PtCsvEff_evtgen,"evtgen","l");
  leg_CSVtagging1->Draw("SAME");

	C_CSVtagging->cd(2);
	h_PtCsvEff_epRatio->GetXaxis()->SetTitle("JetPt");
	h_PtCsvEff_epRatio->Draw();
	// h_PtCsvCut_pythia->Draw();
	// C_CSVtagging->cd(3);
	// h_PtCsvCut_evtgen->Draw();
//	C_CSVtagging->SaveAs("C_CSVtagging.pdf");


	TCanvas *C_Bmesons_nChargeDau_ratio= new TCanvas("C_Bmesons_nChargeDau_ratio","C_Bmesons_nChargeDau_ratio");
	C_Bmesons_nChargeDau_ratio->Divide(2,2);
	C_Bmesons_nChargeDau_ratio->cd(1);
//	h_B0_nChargeDau_epRatio->Divide(h_B0_nChargeDau_pythia);
//	h_B0_nChargeDau_epRatio->Scale(B0_pythia_entries/B0_evtgen_entries);
	h_B0_nChargeDau_epRatio->Divide(h_B0_nChargeDau_epRatio,h_B0_nChargeDau_pythia,B0_pythia_entries,B0_evtgen_entries);
	h_B0_nChargeDau_epRatio->GetXaxis()->SetRange(2,19);
	h_B0_nChargeDau_epRatio->GetXaxis()->SetTitle("number of charge daughters");
	h_B0_nChargeDau_epRatio->SetTitle("B^{0}_nChargeDau_evtgen-pythia6-Ratio");
	h_B0_nChargeDau_epRatio->Draw();

  C_Bmesons_nChargeDau_ratio->cd(2);
  h_Bpm_nChargeDau_epRatio->Divide(h_Bpm_nChargeDau_epRatio,h_Bpm_nChargeDau_pythia,Bpm_pythia_entries,Bpm_evtgen_entries);
  h_Bpm_nChargeDau_epRatio->GetXaxis()->SetRange(2,19);
  h_Bpm_nChargeDau_epRatio->GetXaxis()->SetTitle("number of charge daughters");
  h_Bpm_nChargeDau_epRatio->SetTitle("B^{+}_nChargeDau_evtgen-pythia6-Ratio");
  h_Bpm_nChargeDau_epRatio->Draw();
	
  C_Bmesons_nChargeDau_ratio->cd(3);
  h_Bs_nChargeDau_epRatio->Divide(h_Bs_nChargeDau_epRatio,h_Bs_nChargeDau_pythia,Bs_pythia_entries,Bs_evtgen_entries);
  h_Bs_nChargeDau_epRatio->GetXaxis()->SetRange(2,19);
  h_Bs_nChargeDau_epRatio->GetXaxis()->SetTitle("number of charge daughters");
  h_Bs_nChargeDau_epRatio->SetTitle("B_{S}_nChargeDau_evtgen-pythia6-Ratio");
  h_Bs_nChargeDau_epRatio->Draw();

  C_Bmesons_nChargeDau_ratio->cd(4);
  h_Bmesons_nChargeDau_epRatio->Divide(h_Bmesons_nChargeDau_epRatio,h_Bmesons_nChargeDau_pythia,Bmesons_pythia_entries,Bmesons_evtgen_entries);
  h_Bmesons_nChargeDau_epRatio->GetXaxis()->SetRange(2,19);  
	h_Bmesons_nChargeDau_epRatio->GetXaxis()->SetTitle("number of charge daughters");
  h_Bmesons_nChargeDau_epRatio->SetTitle("Bmesons_nChargeDau_evtgen-pythia6-Ratio");
  h_Bmesons_nChargeDau_epRatio->Draw();

	C_Bmesons_nChargeDau_ratio->SaveAs("Bmesons_nChargeDau_ratio.pdf");


  TCanvas *C_Bmesons_nChargeDau_ratio2= new TCanvas("C_Bmesons_nChargeDau_ratio2","C_Bmesons_nChargeDau_ratio2");
  C_Bmesons_nChargeDau_ratio2->Divide(2,2);
  C_Bmesons_nChargeDau_ratio2->cd(1);
  h_B0_nChargeDau_epRatio->GetXaxis()->SetRange(3,19);
  h_B0_nChargeDau_epRatio->Draw();
 
 C_Bmesons_nChargeDau_ratio2->cd(2);
  h_Bpm_nChargeDau_epRatio->GetXaxis()->SetRange(3,19);
  h_Bpm_nChargeDau_epRatio->Draw();

  C_Bmesons_nChargeDau_ratio2->cd(3);
  h_Bs_nChargeDau_epRatio->GetXaxis()->SetRange(3,19);
  h_Bs_nChargeDau_epRatio->Draw();

  C_Bmesons_nChargeDau_ratio2->cd(4);
  h_Bmesons_nChargeDau_epRatio->GetXaxis()->SetRange(3,19);
  h_Bmesons_nChargeDau_epRatio->Draw();

  C_Bmesons_nChargeDau_ratio2->SaveAs("Bmesons_nChargeDau_ratio2.pdf");




	gStyle->SetOptStat(0);
	double scale=1000;

	TCanvas *C_Bmesons_nChargeDau= new TCanvas("C_Bmesons_nChargeDau","C_Bmesons_nChargeDau");
	C_Bmesons_nChargeDau->Divide(2,2);
	C_Bmesons_nChargeDau->cd(1);
	h_B0_nChargeDau_pythia->Scale(scale/B0_pythia_entries);
	h_B0_nChargeDau_evtgen->Scale(scale/B0_evtgen_entries);
	h_B0_nChargeDau_pythia->SetLineColor(4);
	h_B0_nChargeDau_pythia->SetMarkerColor(4);
	h_B0_nChargeDau_evtgen->SetLineColor(2);
	h_B0_nChargeDau_evtgen->SetMarkerColor(2);

	h_B0_nChargeDau_pythia->GetXaxis()->SetRange(2,19);
	h_B0_nChargeDau_evtgen->GetXaxis()->SetRange(2,19);
	h_B0_nChargeDau_pythia->GetXaxis()->SetTitle("number of charge daughters");

	h_B0_nChargeDau_pythia->SetTitle("B^{0} decays");

	h_B0_nChargeDau_pythia->Draw();
	h_B0_nChargeDau_evtgen->Draw("SAME");


	TLegend *leg_B0 = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_B0->AddEntry(h_B0_nChargeDau_pythia,"pythia6","l");
	leg_B0->AddEntry(h_B0_nChargeDau_evtgen,"evtgen","l");
	leg_B0->Draw();


	C_Bmesons_nChargeDau->cd(2);
	h_Bpm_nChargeDau_pythia->Scale(scale/Bpm_pythia_entries);
	h_Bpm_nChargeDau_evtgen->Scale(scale/Bpm_evtgen_entries);
	h_Bpm_nChargeDau_pythia->SetLineColor(4);
	h_Bpm_nChargeDau_pythia->SetMarkerColor(4);
	h_Bpm_nChargeDau_evtgen->SetLineColor(2);
	h_Bpm_nChargeDau_evtgen->SetMarkerColor(2);

	h_Bpm_nChargeDau_pythia->GetXaxis()->SetRange(2,19);
	h_Bpm_nChargeDau_evtgen->GetXaxis()->SetRange(2,19);
	h_Bpm_nChargeDau_pythia->GetXaxis()->SetTitle("number of charge daughters");

	h_Bpm_nChargeDau_pythia->SetTitle("B^{+} decays");

	h_Bpm_nChargeDau_pythia->Draw();
	h_Bpm_nChargeDau_evtgen->Draw("SAME");


	TLegend *leg_Bpm = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_Bpm->AddEntry(h_Bpm_nChargeDau_pythia,"pythia6","l");
	leg_Bpm->AddEntry(h_Bpm_nChargeDau_evtgen,"evtgen","l");
	leg_Bpm->Draw();

	C_Bmesons_nChargeDau->cd(3);
	h_Bs_nChargeDau_pythia->Scale(scale/Bs_pythia_entries);
	h_Bs_nChargeDau_evtgen->Scale(scale/Bs_evtgen_entries);
	h_Bs_nChargeDau_pythia->SetLineColor(4);
	h_Bs_nChargeDau_pythia->SetMarkerColor(4);
	h_Bs_nChargeDau_evtgen->SetLineColor(2);
	h_Bs_nChargeDau_evtgen->SetMarkerColor(2);

	h_Bs_nChargeDau_pythia->GetXaxis()->SetRange(2,19);
	h_Bs_nChargeDau_evtgen->GetXaxis()->SetRange(2,19);
	h_Bs_nChargeDau_pythia->GetXaxis()->SetTitle("number of charge daughters");

	h_Bs_nChargeDau_pythia->SetTitle("B_{S} decays");

	h_Bs_nChargeDau_pythia->Draw();
	h_Bs_nChargeDau_evtgen->Draw("SAME");


	TLegend *leg_Bs = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_Bs->AddEntry(h_Bs_nChargeDau_pythia,"pythia6","l");
	leg_Bs->AddEntry(h_Bs_nChargeDau_evtgen,"evtgen","l");
	leg_Bs->Draw();

	C_Bmesons_nChargeDau->cd(4);
	h_Bmesons_nChargeDau_pythia->Scale(scale/Bmesons_pythia_entries);
	h_Bmesons_nChargeDau_evtgen->Scale(scale/Bmesons_evtgen_entries);
	h_Bmesons_nChargeDau_pythia->SetLineColor(4);
	h_Bmesons_nChargeDau_pythia->SetMarkerColor(4);
	h_Bmesons_nChargeDau_evtgen->SetLineColor(2);
	h_Bmesons_nChargeDau_evtgen->SetMarkerColor(2);

	h_Bmesons_nChargeDau_pythia->GetXaxis()->SetRange(2,19);
	h_Bmesons_nChargeDau_evtgen->GetXaxis()->SetRange(2,19);
	h_Bmesons_nChargeDau_pythia->GetXaxis()->SetTitle("number of charge daughters");

	h_Bmesons_nChargeDau_pythia->SetTitle("Bmesons decays");

	h_Bmesons_nChargeDau_pythia->Draw("L");
	h_Bmesons_nChargeDau_evtgen->Draw("LSAME");


	TLegend *leg_Bmesons = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_Bmesons->AddEntry(h_Bmesons_nChargeDau_pythia,"pythia6","l");
	leg_Bmesons->AddEntry(h_Bmesons_nChargeDau_evtgen,"evtgen","l");
	leg_Bmesons->Draw();


	C_Bmesons_nChargeDau->SaveAs("Bmesons_nChargeDau.pdf");



	// C_B0_decay->SaveAs("B0_decay.pdf");
	/*
		 TCanvas *C_Bmesons_nChargeDau_ratio= new TCanvas("C_Bmesons_nChargeDau_ratio","C_Bmesons_nChargeDau_ratio");
		 C_Bmesons_nChargeDau_ratio->Divide(2,2);
		 C_Bmesons_nChargeDau_ratio->cd(1); 
		 TH1F *h_B0_nChargeDau_epRatio=(TH1F*)h_B0_nChargeDau_pythia->Clone("h_B0_nChargeDau_epRatio");
		 h_B0_nChargeDau_epRatio->Divide(h_B0_nChargeDau_evtgen);
	//	h_B0_nChargeDau_epRatio->Divide(h_B0_nChargeDau_epRatio,h_B0_nChargeDau_pythia,B0_pythia_entries,B0_evtgen_entries);
	h_B0_nChargeDau_epRatio->GetXaxis()->SetRange(2,19);
	h_B0_nChargeDau_epRatio->Draw();
	*/




	/*

		 TCanvas *C_B0_decay = new TCanvas("C_B0_decay","C_B0_decay");
	//	C_B0_decay->Divide(2,1);
	C_B0_decay->cd(1);
	double B0_pythia_entries= (double)h_B0_decay_pythia->GetEntries();
	double B0_evtgen_entries= (double)h_B0_decay_evtgen->GetEntries();

	double B0_pythia_n1= (double)h_B0_decay_pythia->GetBinContent(3);
	double B0_pythia_n2= (double)h_B0_decay_pythia->GetBinContent(4);
	double B0_pythia_n3= (double)h_B0_decay_pythia->GetBinContent(5);
	double B0_pythia_n4= (double)h_B0_decay_pythia->GetBinContent(6);
	double B0_pythia_n5= (double)h_B0_decay_pythia->GetBinContent(7);
	double B0_pythia_n6= (double)h_B0_decay_pythia->GetBinContent(8);
	double B0_pythia_n7= (double)h_B0_decay_pythia->GetBinContent(9);

	cout<<"B0_pythia_entries = "<<B0_pythia_entries<<" , B0_pythia_n1 = "<<B0_pythia_n1<<" , ratio= "<<B0_pythia_n1/B0_pythia_entries<<endl;
	cout<<" ratio1 = "<<B0_pythia_n1/B0_pythia_entries<<endl;
	cout<<" ratio2 = "<<B0_pythia_n2/B0_pythia_entries<<endl;
	cout<<" ratio3 = "<<B0_pythia_n3/B0_pythia_entries<<endl;
	cout<<" ratio4 = "<<B0_pythia_n4/B0_pythia_entries<<endl;
	cout<<" ratio5 = "<<B0_pythia_n5/B0_pythia_entries<<endl;
	cout<<" ratio6 = "<<B0_pythia_n6/B0_pythia_entries<<endl;
	cout<<" ratio7 = "<<B0_pythia_n7/B0_pythia_entries<<endl;

	double B0_evtgen_n1= (double)h_B0_decay_evtgen->GetBinContent(3);
	double B0_evtgen_n2= (double)h_B0_decay_evtgen->GetBinContent(4);
	double B0_evtgen_n3= (double)h_B0_decay_evtgen->GetBinContent(5);
	double B0_evtgen_n4= (double)h_B0_decay_evtgen->GetBinContent(6);
	double B0_evtgen_n5= (double)h_B0_decay_evtgen->GetBinContent(7);
	double B0_evtgen_n6= (double)h_B0_decay_evtgen->GetBinContent(8);
	double B0_evtgen_n7= (double)h_B0_decay_evtgen->GetBinContent(9);

	cout<<"B0_evtgen_entries = "<<B0_evtgen_entries<<" , B0_evtgen_n1 = "<<B0_evtgen_n1<<" , ratio= "<<B0_evtgen_n1/B0_evtgen_entries<<endl;
	cout<<" ratio1 = "<<B0_evtgen_n1/B0_evtgen_entries<<endl;
	cout<<" ratio2 = "<<B0_evtgen_n2/B0_evtgen_entries<<endl;
	cout<<" ratio3 = "<<B0_evtgen_n3/B0_evtgen_entries<<endl;
	cout<<" ratio4 = "<<B0_evtgen_n4/B0_evtgen_entries<<endl;
	cout<<" ratio5 = "<<B0_evtgen_n5/B0_evtgen_entries<<endl;
	cout<<" ratio6 = "<<B0_evtgen_n6/B0_evtgen_entries<<endl;
	cout<<" ratio7 = "<<B0_evtgen_n7/B0_evtgen_entries<<endl;



	h_B0_decay_pythia->Scale(scale_factor/B0_pythia_entries);
	h_B0_decay_evtgen->Scale(scale_factor/B0_evtgen_entries);

	h_B0_decay_evtgen->GetXaxis()->SetRange(3,10);
	//	h_B0_decay_evtgen->SetMarkerColor(1);
	h_B0_decay_evtgen->SetLineColor(2);
	h_B0_decay_evtgen->SetMarkerStyle(3);
	h_B0_decay_evtgen->SetMarkerColor(2);
	h_B0_decay_pythia->SetMarkerStyle(3);
	h_B0_decay_pythia->SetMarkerColor(4);
	h_B0_decay_pythia->SetLineColor(4);
	h_B0_decay_pythia->GetXaxis()->SetRange(3,10);
	h_B0_decay_pdg->GetXaxis()->SetRange(3,10);

	h_B0_decay_pythia->SetTitle("B^{0} decays");

	h_B0_decay_pythia->Draw();
	h_B0_decay_evtgen->Draw("SAME");
	h_B0_decay_pdg->Draw("PSAME");
	h_B0_decay_table->Draw("PSAME");

	TLegend *leg_B0 = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_B0->AddEntry(h_B0_decay_pythia,"pythia6","p");
	leg_B0->AddEntry(h_B0_decay_evtgen,"evtgen","p");
	leg_B0->AddEntry(h_B0_decay_table,"evtgen_table","p");
	leg_B0->AddEntry(h_B0_decay_pdg,"pdg","p");
	leg_B0->Draw();

	C_B0_decay->SaveAs("B0_decay.pdf");



	TCanvas *C_B0bar_decay = new TCanvas("C_B0bar_decay","C_B0bar_decay");
	C_B0bar_decay->cd(1);
	double B0bar_pythia_entries= (double)h_B0bar_decay_pythia->GetEntries();
	double B0bar_evtgen_entries= (double)h_B0bar_decay_evtgen->GetEntries();
	h_B0bar_decay_pythia->Scale(scale_factor/B0bar_pythia_entries);
	h_B0bar_decay_evtgen->Scale(scale_factor/B0bar_evtgen_entries);

	h_B0bar_decay_evtgen->GetXaxis()->SetRange(3,10);
	h_B0bar_decay_evtgen->SetMarkerColor(2);
	h_B0bar_decay_evtgen->SetMarkerStyle(4);
	h_B0bar_decay_evtgen->SetLineColor(2);
	h_B0bar_decay_pythia->GetXaxis()->SetRange(3,10);
	h_B0bar_decay_pythia->SetMarkerStyle(4);
	h_B0bar_decay_pythia->SetMarkerColor(4);
	h_B0bar_decay_pythia->SetLineColor(4);
	//  h_B0bar_decay_pdg->GetXaxis()->SetRange(3,10);
	h_B0bar_decay_pythia->SetTitle("B^{0}/B^{0}bar decays");

	h_B0bar_decay_pythia->Draw();
	h_B0_decay_pythia->Draw("PSAME");
	h_B0bar_decay_evtgen->Draw("PSAME");
	h_B0_decay_evtgen->Draw("PSAME");
	TLegend *leg_B0bar = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_B0bar->AddEntry(h_B0_decay_pythia,"pythia6_B0","p");
	leg_B0bar->AddEntry(h_B0bar_decay_pythia,"pythia6_B0bar","p");
	leg_B0bar->AddEntry(h_B0_decay_evtgen,"evtgen_B0","p");
	leg_B0bar->AddEntry(h_B0bar_decay_evtgen,"evtgen_B0bar","p");
	leg_B0bar->Draw();

	C_B0bar_decay->SaveAs("B0bar_decay.pdf");


	//  h_B0bar_decay_pdg->Draw("PSAME");

	TCanvas *C_Bp_decay = new TCanvas("C_Bp_decay","C_Bp_decay");
	double Bp_pythia_entries= (double)h_Bp_decay_pythia->GetEntries();
	double Bp_evtgen_entries= (double)h_Bp_decay_evtgen->GetEntries();
	h_Bp_decay_pythia->Scale(scale_factor/Bp_pythia_entries);
	h_Bp_decay_evtgen->Scale(scale_factor/Bp_evtgen_entries);

	h_Bp_decay_evtgen->GetXaxis()->SetRange(3,10);
	h_Bp_decay_evtgen->SetMarkerColor(2);
	h_Bp_decay_evtgen->SetMarkerStyle(2);
	h_Bp_decay_evtgen->SetLineColor(2);
	h_Bp_decay_pythia->GetXaxis()->SetRange(3,10);
	h_Bp_decay_pythia->SetMarkerStyle(2);
	h_Bp_decay_pythia->SetMarkerColor(4);
	h_Bp_decay_pythia->SetLineColor(4);
	//  h_Bp_decay_pdg->GetXaxis()->SetRange(3,10);
	h_Bp_decay_pythia->SetTitle("B^{+} decays");

	h_Bp_decay_pythia->Draw();
	h_Bp_decay_evtgen->Draw("PSAME");
	h_Bp_decay_pdg->Draw("PSAME");
	TLegend *leg_Bp = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_Bp->AddEntry(h_Bp_decay_pythia,"pythia6_Bp","p");
	leg_Bp->AddEntry(h_Bp_decay_evtgen,"evtgen_Bp","p");
	leg_Bp->AddEntry(h_Bp_decay_pdg,"pdg_Bp","p");
	leg_Bp->Draw();

	C_Bp_decay->SaveAs("Bp_decay.pdf");



	TCanvas *C_Bs_decay = new TCanvas("C_Bs_decay","C_Bs_decay");
	double Bs_pythia_entries= (double)h_Bs_decay_pythia->GetEntries();
	double Bs_evtgen_entries= (double)h_Bs_decay_evtgen->GetEntries();
	h_Bs_decay_pythia->Scale(scale_factor/Bs_pythia_entries);
	h_Bs_decay_evtgen->Scale(scale_factor/Bs_evtgen_entries);

	h_Bs_decay_evtgen->GetXaxis()->SetRange(3,10);
	h_Bs_decay_evtgen->SetMarkerColor(2);
	h_Bs_decay_evtgen->SetMarkerStyle(2);
	h_Bs_decay_evtgen->SetLineColor(2);
	h_Bs_decay_pythia->GetXaxis()->SetRange(3,10);
	h_Bs_decay_pythia->SetMarkerStyle(2);
	h_Bs_decay_pythia->SetMarkerColor(4);
	h_Bs_decay_pythia->SetLineColor(4);
	//  h_Bs_decay_pdg->GetXaxis()->SetRange(3,10);
	h_Bs_decay_pythia->SetTitle("B_{S} decays");

	h_Bs_decay_pythia->Draw();
	h_Bs_decay_evtgen->Draw("PSAME");
	h_Bs_decay_pdg->Draw("PSAME");

	TLegend *leg_Bs = new TLegend(0.75,0.75,0.9,0.9);
	//  leg->SetHeader("header");
	leg_Bs->AddEntry(h_Bs_decay_pythia,"pythia6_Bs","p");
	leg_Bs->AddEntry(h_Bs_decay_evtgen,"evtgen_Bs","p");
	leg_Bs->AddEntry(h_Bs_decay_pdg,"pdg_Bs","p");
	leg_Bs->Draw();

	C_Bs_decay->SaveAs("Bs_decay.pdf");

	// work on TLegend.
	*/
}
