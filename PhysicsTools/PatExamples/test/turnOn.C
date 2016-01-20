void turnOn(){
  TFile * f = new TFile("analyzePatTrigger_onTheFly.root");
  
  TH1D * matched = (TH1D*) f->Get("triggerAnalysis/turnOn");
  TH1D * recoCand = (TH1D*) f->Get("triggerAnalysis/recoCand");

  TCanvas * c_matched= new TCanvas("c_matched","c_matched",1);
  matched->Draw();
  matched->SetTitle("Triggered Muon Object");
  matched->GetXaxis()->SetTitle("Matched Object Transverse Momentum (GeV)");
  TCanvas * c_recoCand = new TCanvas("c_recoCand","c_recoCand",1);
  recoCand->Draw();
  recoCand->SetTitle("Muon Object");
  recoCand->GetXaxis()->SetTitle("Muon Object Transverse Momentum (GeV)");

  TCanvas * c_turnOn = new TCanvas("c_turnOn","c_turnOn",1);
  TH1D * turnOn = (TH1D *) matched->Clone();
  turnOn->Divide(recoCand);
  turnOn->Draw();
  turnOn->SetTitle("Trigger Efficiency");

}
