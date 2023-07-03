import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';
import * as serviceWorkerRegistration from './serviceWorkerRegistration';
import reportWebVitals from './reportWebVitals';
import {Amplify} from "aws-amplify"
import awsconfig from './aws-exports';
Amplify.configure(awsconfig);

// Amplify.configure({
//   Auth: {
//     // REQUIRED - Amazon Cognito Region
//     identityPoolId: "ap-south-1:8921cea3-93a6-4007-984b-477153841c",
//     region: "ap-south-1",
//     authenticationFlowType: "CUSTOM_AUTH",
//     userPoolId: "ap-south-1_erFTVT",
//     userPoolWebClientId: "44gb2te0v45hf5vjnem8n",
//     PushNotification: {
//       appId: "1:478239037100:android:68505a7ebdf7141ff97109",
//       requestIOSPermissions: false,
//     },
//   },
// });


const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  // <React.StrictMode>
    <App />
  // </React.StrictMode>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
serviceWorkerRegistration.register();

