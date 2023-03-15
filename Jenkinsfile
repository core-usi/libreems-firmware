pipeline {
    agent any
    
     parameters {
        string(name: 'repo_branch', defaultValue: 'feature_DCP-1', description: 'feature branch repo name')
     }

    stages {
        stage('Sonar scan') {
            steps {
                cleanWs()
            
               
                
                sh '''
                echo $params.repo_branch
                rm -rf libreems-firmware
                git clone -b $params.repo_branch https://github.com/core-usi/libreems-firmware.git 
                
                ls
                cd ./libreems-firmware
                ls
                pwd
                /tmp/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir bw-output cmake -S . -B .
                /tmp/sonar-scanner-4.8.0.2856-linux/bin/sonar-scanner -Dsonar.projectKey=DevOps_Cloud_Platform_int -Dsonar.sources=. -Dsonar.cfamily.build-wrapper-output=bw-output -Dsonar.host.url=https://globalsonarqube.deloitte.com -Dsonar.login=2329c90856495708517a8fa98f1a7d9d82c6105b
                
                '''
            }
        }
    }
}
