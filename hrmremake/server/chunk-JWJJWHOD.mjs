import './polyfills.server.mjs';
import{qa as c}from"./chunk-PBTJ7KBG.mjs";import{b as d}from"./chunk-LH2VRXI6.mjs";import{$ as n,W as h,f as m,fb as f,o as s}from"./chunk-DQBLOAAZ.mjs";import{h as r}from"./chunk-VVCT4QZE.mjs";var F=(()=>{class i{constructor(t,e){this.http=t,this.notifiServ=e,this.baseUrl="http://localhost:7033/api/CandidateData",this.baseUrlFile="http://localhost:7033/api/",this.resulstLength=f(0),this.loadingResults=f(!0),this.triggerFunctionSub=new m,this.triggerFunction$=this.triggerFunctionSub.asObservable()}AddCandidate(t){return this.http.post(`${this.baseUrl}/CreateCandidate`,t)}FindCandidateInfo(t){return this.http.get(`${this.baseUrl}/CandidateInfo?candidateID=${t}`)}fetchCandidateData(t,e){return r(this,null,function*(){try{let a=yield s(this.http.get(`${this.baseUrl}/FetchCandidates?pageSize=${t}&pageNumber=${e}`));return this.loadingResults.update(o=>o=!1),this.resulstLength.update(o=>o=a.numOfCandidates),a.Data}catch(a){throw a}})}fetchCandidateBySearchParameter(t,e,a,o,b,g,w,C){return r(this,null,function*(){try{let l={searchParameter:t,searchParameterGrade:e,Date_of_application_Start:a,Date_of_application_End:o,Date_of_interview_Start:b,Date_of_interview_End:g},p=yield s(this.http.post(`${this.baseUrl}/SearchCandidates?pageSize=${w}&pageNumber=${C}`,l));return console.log(p),this.loadingResults.update(u=>u=!1),this.resulstLength.update(u=>u=p.numOfCandidates),p.Data}catch(l){throw l}})}UpdateCandidate(t,e){return this.http.put(this.baseUrl+"/UpdateCandidate?candidateID="+t,e)}UploadFile(t,e){return this.http.post(this.baseUrlFile+"CandidateFiles",t,e)}DownloadFile(t){return this.http.get(this.baseUrlFile+"CandidateFiles?id="+t,{responseType:"blob"})}DeleteCandidate(t){return r(this,null,function*(){try{let e=yield s(this.http.delete(this.baseUrl+"?id="+t));return this.notifiServ.openSnackbar("Candidate deleted successfully!"),e.Data}catch(e){throw e}})}executeSessionStorageSaving(){this.triggerFunctionSub.next()}static{this.\u0275fac=function(e){return new(e||i)(n(d),n(c))}}static{this.\u0275prov=h({token:i,factory:i.\u0275fac,providedIn:"root"})}}return i})();var _=(()=>{class i{constructor(t,e){this.http=t,this.notifiServ=e,this.baseUrl="http://localhost:7033/api/Interview",this.requestedOptions={withCredentials:!1}}AddInterview(t,e){return this.http.post(`${this.baseUrl}?email=${e}`,t)}GetCandidateInterview(t){return this.http.get(`${this.baseUrl}/CandidateInterview?candidateID=${t}`)}UpdateInterview(t,e){return this.http.put(`${this.baseUrl}/UpdateInterview?id=${t}`,e)}DeleteInterview(t){return r(this,null,function*(){try{let e=yield s(this.http.delete(this.baseUrl+"?id="+t));return this.notifiServ.openSnackbar("Interview deleted successfully!"),e.Data}catch(e){throw e}})}static{this.\u0275fac=function(e){return new(e||i)(n(d),n(c))}}static{this.\u0275prov=h({token:i,factory:i.\u0275fac,providedIn:"root"})}}return i})();export{F as a,_ as b};
