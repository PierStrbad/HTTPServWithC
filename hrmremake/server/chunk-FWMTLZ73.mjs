import './polyfills.server.mjs';
import{qa as m}from"./chunk-42VY2SIW.mjs";import{b as d}from"./chunk-LH2VRXI6.mjs";import{$ as s,W as h,f,fb as u,o}from"./chunk-DQBLOAAZ.mjs";import{h as n}from"./chunk-VVCT4QZE.mjs";var y=(()=>{class i{constructor(t,e){this.http=t,this.notifiServ=e,this.baseUrl="http://localhost:7033/api/CandidateData",this.baseUrlFile="http://localhost:7033/api/",this.resulstLength=u(0),this.loadingResults=u(!0),this.triggerFunctionSub=new f,this.triggerFunction$=this.triggerFunctionSub.asObservable()}AddCandidate(t){return this.http.post(`${this.baseUrl}/CreateCandidate`,t)}FindCandidateInfo(t){return this.http.get(`${this.baseUrl}/CandidateInfo?email=${t}`)}fetchCandidateData(t,e){return n(this,null,function*(){try{let a=yield o(this.http.get(`${this.baseUrl}/FetchCandidates?pageSize=${t}&pageNumber=${e}`));return this.loadingResults.update(r=>r=!1),this.resulstLength.update(r=>r=a.numOfCandidates),a.Data}catch(a){throw a}})}fetchCandidateBySearchParameter(t,e,a,r,b,g,C,w){return n(this,null,function*(){try{let l={searchParameter:t,searchParameterGrade:e,Date_of_application_Start:a,Date_of_application_End:r,Date_of_interview_Start:b,Date_of_interview_End:g},p=yield o(this.http.post(`${this.baseUrl}/SearchCandidates?pageSize=${C}&pageNumber=${w}`,l));return console.log(p),this.loadingResults.update(c=>c=!1),this.resulstLength.update(c=>c=p.numOfCandidates),p.Data}catch(l){throw l}})}UpdateCandidate(t,e){return this.http.put(this.baseUrl+"/UpdateCandidate?email="+t,e)}UploadFile(t,e){return this.http.post(this.baseUrlFile+"CandidateFiles",t,e)}DownloadFile(t){return this.http.get(this.baseUrlFile+"CandidateFiles?id="+t,{responseType:"blob"})}DeleteCandidate(t){return n(this,null,function*(){try{let e=yield o(this.http.delete(this.baseUrl+"?id="+t));return this.notifiServ.openSnackbar("Candidate deleted successfully!"),e.Data}catch(e){throw e}})}executeSessionStorageSaving(){this.triggerFunctionSub.next()}static{this.\u0275fac=function(e){return new(e||i)(s(d),s(m))}}static{this.\u0275prov=h({token:i,factory:i.\u0275fac,providedIn:"root"})}}return i})();var j=(()=>{class i{constructor(t){this.http=t,this.baseUrl="http://localhost:7033/api/Interview",this.requestedOptions={withCredentials:!1}}AddInterview(t,e){return this.http.post(`${this.baseUrl}?email=${e}`,t)}GetCandidateInterview(t){return this.http.get(`${this.baseUrl}/CandidateInterview?email=${t}`)}UpdateInterview(t,e){return this.http.put(`${this.baseUrl}/UpdateInterview?id=${t}`,e)}static{this.\u0275fac=function(e){return new(e||i)(s(d))}}static{this.\u0275prov=h({token:i,factory:i.\u0275fac,providedIn:"root"})}}return i})();export{y as a,j as b};
