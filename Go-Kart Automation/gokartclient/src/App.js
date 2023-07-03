import logo from './logo.svg';
import './App.css';
import {useEffect, useState} from "react";
import { Amplify, PubSub,Auth } from 'aws-amplify';
import { AWSIoTProvider } from '@aws-amplify/pubsub';
import { withAuthenticator } from '@aws-amplify/ui-react';
import '@aws-amplify/ui-react/styles.css';
import Map from './Map';
import {Container,Row, Button, Form} from 'react-bootstrap'
// import {}/

Amplify.addPluggable(
  new AWSIoTProvider({
    aws_pubsub_region: 'ap-south-1',
    aws_pubsub_endpoint:
      'wss://a37nlo9ieaaf6l-ats.iot.ap-south-1.amazonaws.com/mqtt'
      
  })  
);


Auth.currentCredentials().then((info) => {
  const cognitoIdentityId = info.identityId;
  console.log(cognitoIdentityId);
});

const publish = (topic,status)=>{
  console.log("pub");
  PubSub.publish(topic, { status: status });
}

function App() {
  const [lat,setLat]=useState(null);
  const [lng,setLng]=useState(null);
  const [cam,setCam]=useState('localhost:3000');
  const [isCam,setIsCam]=useState(null);
  const [isFinger,setIsFinger]=useState(null);
  const [BPM,setBPM]=useState(null);
  const [RotX,setRotX]=useState(null);
  const [RotY,setRotY]=useState(null);
  const [RotZ,setRotZ]=useState(null);
  const [AccX,setAccX]=useState(null);
  const [AccY,setAccY]=useState(null);
  const [AccZ,setAccZ]=useState(null);
  const [light,setLight]=useState(null);

  const [flash, setflash] = useState(false)
  const [headlight, setheadlight] = useState(false)
  const [buzzer, setbuzzer] = useState(false)
  const [extra1, setextra1] = useState(false)
  const [extra2, setextra2] = useState(false)
  const [emergency, setemergency] = useState(false)
  const [emergencySwitch, setemergencySwitch] = useState(false)
  const [rfid, setrfid] = useState(null )
  const [cameraiframe, setcameraiframe] = useState(null )

  const onSwitchFlash= ()=>{
    if(flash){
      setflash(false)
      publish('setFlash', '1')
    }else{
      setflash(true)
      publish('setFlash', '0')
    }
  }

  const onSwitchHeadlight= ()=>{
    if(headlight){
      setheadlight(false)
      publish('setHeadlight', '0')
    }else{
      setheadlight(true)
      publish('setHeadlight', '1')
    }
  }

  const onSwitchBuzzer= ()=>{
    if(buzzer){
      setbuzzer(false)
      publish('setBuzzer', '0')
    }else{
      setbuzzer(true)
      publish('setBuzzer', '1')
    }
  }
  const onSwitchIsCam= ()=>{
    if(isCam){
      setIsCam(false)
      
    }else{
      setIsCam(true)
      
    }
  }

  const onSwitchExtra1= ()=>{
    if(extra1){
      setextra1(false)
      publish('setExtra1', '0')
    }else{
      setextra1(true)
      publish('setExtra1', '1')
    }
  }

  const onSwitchExtra2= ()=>{
    if(extra2){
      setextra2(false)
      publish('setExtra2', '0')
    }else{
      setextra2(true)
      publish('setExtra2', '1')
    }
  }

  const onSwitchEmergency= ()=>{
    if(emergency){
      setemergency(false)
    }else{
      console.log('emergency')
      setemergency(true)
    }
  }
  const emergencyCallHandler = ()=>{
    if(emergencySwitch){
      publish('setBuzzer', '1')
      setemergencySwitch(false)
    }else{
      publish('setBuzzer', '0')
      setemergencySwitch(true)
    }
  }

  useEffect(()=>{
    setInterval(()=>{
      console.log('emergency switching: ', emergency)

      if(emergency){
           emergencyCallHandler()
           console.log('emergency switching1')
        }
      }, 3000)
    },[emergency, emergencySwitch])

  useEffect(()=>{
    if(RotX>90 || RotX<-90 || RotY>90 || RotY<-90){
      setemergency(true);
    }
    console.log(`https://www.openstreetmap.org/export/embed.html?bbox=${(parseFloat(lng)-0.02).toString()}%2C${(parseFloat(lat)-0.02).toString()}%2C${(parseFloat(lng)+0.02).toString()}%2C${(parseFloat(lat)+0.02).toString()}&marker=${lat}%2C${lng}&layers=ND`)
  },[RotX, RotY])

  useEffect(()=>{
    if(parseInt(light)>2500){
      onSwitchHeadlight();
    }
  },[light])
  
  
  
  useEffect(()=>{
    PubSub.subscribe('getgps').subscribe({
      next: data => {
        console.log('Message received', data.value);
        setLat(data.value.lat);
        setLng(data.value.lng);
        setCam(data.value.cam);
        console.log(`http://${data.value.cam}`);
        setcameraiframe(<iframe title='cam' id='cam' src={`http://${data.value.cam}`}/>)
        console.log("HAHAHAHAH");
      },
      error: error => console.error(error),
      complete: () => console.log('Done'),
    });
    PubSub.subscribe('getrfid').subscribe({
      next: data => {
        console.log('Message received', data.value);
        setrfid(data.value.rfid);
      },
      error: error => console.error(error),
      complete: () => console.log('Done'),
    });
    PubSub.subscribe('getall2').subscribe({
      next: data => {
        console.log('Message received', data.value);
        setIsFinger(data.value.isFinger)
        setBPM(data.value.BPM)
        setRotX(data.value.RotX)
        setRotY(data.value.RotY)
        setRotZ(data.value.RotZ)
        setAccX(data.value.AccX)
        setAccY(data.value.AccY)
        setAccZ(data.value.AccZ)
        setLight(data.value.Light)
        // "isFinger": "NO",
        // "BPM": "0",
        // "RotX": "172.62",
        // "RotY": "60.96",
        // "RotZ": "315.68",
        // "Light": "3735"
      },
      error: error => console.error(error),
      complete: () => console.log('Done'),
    });
  },)

  return (
    <Container color='red' >

<br/>
        <div className='text-center' style={{width:'100%'}}> <img className='img-fluid text-center' width={'20%'} src='./logo512.png'/></div>
        <h1 style={{paddingTop: '3rem', paddingBottom:'3rem', textAlign:'center'}}>
          Macheetah</h1>


        <Form style={{fontSize: '1rem'}} className='row'>
          <Form.Check 
            type="switch"
            id="flash"
            label="Flash"
            checked={flash}
            onChange={onSwitchFlash}
            style={{width:'50%'}}
          />
          <Form.Check 
            type="switch"
            id="headlight"
            label="Headlight"
            checked={headlight}
            onChange={onSwitchHeadlight}
            style={{width:'50%' }}

          />
          <Form.Check 
            type="switch"
            id="buzzer"
            label="Buzzer"
            checked={buzzer}
            onChange={onSwitchBuzzer}
            style={{width:'50%'}}

          />
          <Form.Check 
            type="switch"
            id="extra1"
            label="Start"
            checked={extra1}
            onChange={onSwitchExtra1}
            style={{width:'50%'}}

          />
          <Form.Check 
            type="switch"
            id="extra2"
            label="Stop"
            checked={extra2}
            onChange={onSwitchExtra2}
            style={{width:'50%'}}

          />
          <Form.Check 
            type="switch"
            id="emergency"
            label="Emergency"
            checked={emergency}
            onChange={onSwitchEmergency}
            style={{width:'50%'}}
          />

          <Form.Check 
            type="switch"
            id="sam"
            label="Camera"
            checked={isCam}
            onChange={onSwitchIsCam}
            style={{width:'50%'}}
          />

          <Button onClick={()=>{
              var xhr = new XMLHttpRequest();

              xhr.open('GET', `http://${cam}`);
              xhr.onreadystatechange = handler;
              xhr.responseType = 'blob';
              // xhr.setRequestHeader('Authorization', 'Bearer ' + token);
              xhr.send();
              function handler() {
                if (this.readyState === this.DONE) {
                  if (this.status === 200) {
                    // this.response is a Blob, because we set responseType above
                    var data_url = URL.createObjectURL(this.response);
                    document.querySelector('#output-frame-id').src = data_url;
                  } else {
                    console.error('no pdf :(');
                  }
                }
              }
              
              // var iframe = document.getElementById('cam'); 
              // iframe.src = iframe.src
            }}>Refresh Cam</Button>

        </Form>
        {emergencySwitch && <h2 style={{color:'red', textAlign:'center'}}>Emergency!!!!</h2>}

        {cam && isCam && <div>{cameraiframe}</div>}

        {lat && 
          <iframe width={"600px" }
              height={"400px" }
              title='map'
              src={`https://www.openstreetmap.org/export/embed.html?bbox=${(parseFloat(lng)-0.02).toString()}%2C${(parseFloat(lat)-0.02).toString()}%2C${(parseFloat(lng)+0.02).toString()}%2C${(parseFloat(lat)+0.02).toString()}&marker=${lat}%2C${lng}&layers=ND`}
              style={{border: '1px solid black'}}/>
        }

        <p>Latitude: </p>{lat && <p>{lat}</p>}
        <p>Longitude: </p>{lng && <p>{lng}</p>}
        <p>Cam IP: </p>{cam && <p>{cam}</p>}
        <p> Finger on Steering?: </p>{isFinger && <p>{isFinger}</p>}
        <p>BPM: </p>{BPM && <p>{BPM}</p>}
        <p>Rotation in X Axis: </p>{RotX && <p>{RotX}</p>}
        <p>Rotation in Y Axis: </p>{RotY && <p>{RotY}</p>}
        <p>Rotation in Z Axis: </p>{RotZ && <p>{RotZ}</p>}
        <p>Accelaration in X Axis: </p>{AccX && <p>{AccX}</p>}
        <p>Accelaration in Y Axis: </p>{AccY && <p>{AccY}</p>}
        <p>Accelaration in Z Axis: </p>{AccZ && <p>{AccZ}</p>}
        <p>Light Value: </p>{light && <p>{light}</p>}
        <p>RFID: </p>{rfid && <p>{rfid}</p>}

        
        <Row><Button onClick={()=>Auth.signOut()}>Log Out</Button></Row>
    </Container>     
  );
}

export default withAuthenticator(App);
