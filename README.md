# UnrealEnginePlugin
Official Unreal Engine plugin for Stratis Blockchain Platform.

> If you are looking for a plugin for Unity Engine, [check this repository](https://github.com/stratisproject/Unity3dIntegration).

This plugin provides functionallity for creating a wallet, building different types of transactions and interacting with [smart contracts](https://academy.stratisplatform.com/Architecture%20Reference/SmartContracts/smartcontracts-introduction.html).

### Modules reference
* **Blockchain** - contains core logic for building wallet & transactions. Usualy, you don't need to interact with it directly.
* **BlockchainTests** - tests for Blockchain module, nothing interesting.
* **Stratis** - entrypoint module, provides `C++`- & `Blueprints`- friendly interfaces for plugin's users. This module should be considered as the only module you need to depend on.
* **StratisAPI** - contains HTTP- & JSON parsing- related code used to interact with [FullNode's lightweight API](https://github.com/stratisproject/StratisFullNode/tree/master/src/Stratis.Features.Unity3dApi). This module was auto-generated using [OpenAPI generator for UE4](https://openapi-generator.tech/docs/generators/cpp-ue4/).
* **Wallet** - contains a modified version of [Trustwallet's Core library](https://github.com/trustwallet/wallet-core).

### Basic usage

`UStratisUnrealManager` should be used as the main entry-point for all Stratis-related actions (except StandardToken & NFT interaction).

`UStandardTokenWrapper` is a high-level wrapper for [standard token](https://ethereum.org/en/developers/docs/standards/tokens/erc-20/) contracts.

`UNFTWrapper` is a high-level wrapper for [non-fungible token](https://ethereum.org/en/developers/docs/standards/tokens/erc-721/) contracts.

### Tutorials

Check our [Wiki page](https://github.com/stratisproject/UnrealEnginePlugin/wiki).
